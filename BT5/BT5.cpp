/*
 * BT5: Phan cong shipper cho don hang theo khoang cach
 * Thuat toan: Min-Cost Max-Flow (MCMF) su dung SPFA (Bellman-Ford)
 * 
 * Mo hinh:
 *   - Do thi hai phan: Shipper (ben trai) <-> Don hang (ben phai)
 *   - Source -> Shipper (cap=1, cost=0)
 *   - Don hang -> Sink (cap=1, cost=0)  
 *   - Shipper -> Don hang (cap=1, cost=w)
 *   - Tim luong cuc dai voi chi phi nho nhat
 *
 * Input:
 *   Dong 1: n m (so dinh, so canh)
 *   m dong tiep: u v w (canh giua shipper u va don v voi trong so w)
 *
 * Output:
 *   Dong 1: s W (so cap ghep cuc dai, tong trong so nho nhat)
 *   s dong tiep: u v (cac canh trong bo ghep)
 */

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// ======================== CAU TRUC MIN-COST MAX-FLOW ========================

struct Edge {
    int to, cap, cost, flow;
};

struct MinCostMaxFlow {
    int n;
    vector<Edge> edges;
    vector<vector<int>> graph;

    MinCostMaxFlow(int n) : n(n), graph(n) {}

    void addEdge(int from, int to, int cap, int cost) {
        graph[from].push_back(edges.size());
        edges.push_back({to, cap, cost, 0});
        graph[to].push_back(edges.size());
        edges.push_back({from, 0, -cost, 0});
    }

    // SPFA (Shortest Path Faster Algorithm) de tim duong tang voi chi phi nho nhat
    bool spfa(int s, int t, vector<int>& dist, vector<int>& parent, vector<int>& augment) {
        dist.assign(n, INF);
        parent.assign(n, -1);
        augment.assign(n, 0);
        vector<bool> inQueue(n, false);

        dist[s] = 0;
        augment[s] = INF;
        inQueue[s] = true;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;

            for (int id : graph[u]) {
                Edge& e = edges[id];
                if (e.cap > e.flow && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    parent[e.to] = id;
                    augment[e.to] = min(augment[u], e.cap - e.flow);
                    if (!inQueue[e.to]) {
                        inQueue[e.to] = true;
                        q.push(e.to);
                    }
                }
            }
        }
        return dist[t] != INF;
    }

    // Giai MCMF: tra ve (max_flow, min_cost)
    pair<int, int> solve(int s, int t) {
        int totalFlow = 0, totalCost = 0;
        vector<int> dist, parent, augment;

        while (spfa(s, t, dist, parent, augment)) {
            totalFlow += augment[t];
            totalCost += augment[t] * dist[t];

            // Cap nhat luong tren duong tang
            int u = t;
            while (u != s) {
                edges[parent[u]].flow += augment[t];
                edges[parent[u] ^ 1].flow -= augment[t];
                u = edges[parent[u] ^ 1].to;
            }
        }
        return {totalFlow, totalCost};
    }
};

// ======================== CHUONG TRINH CHINH ========================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Doc danh sach canh
    vector<tuple<int, int, int>> edgeList(m);
    vector<vector<pair<int, int>>> adj(n + 1); // danh sach ke de to mau

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edgeList[i] = {u, v, w};
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    // ===== BUOC 1: To mau 2 phia (BFS) de xac dinh Shipper va Don hang =====
    vector<int> color(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0; // 0 = Shipper (ben trai), 1 = Don hang (ben phai)
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (auto& [v, idx] : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    }
                }
            }
        }
    }

    // ===== BUOC 2: Xay dung mang luong =====
    int S = 0, T = n + 1; // Source = 0, Sink = n+1
    MinCostMaxFlow mcmf(n + 2);

    // Source -> Shipper (color=0), Don hang (color=1) -> Sink
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            mcmf.addEdge(S, i, 1, 0);
        } else {
            mcmf.addEdge(i, T, 1, 0);
        }
    }

    // Ghi nho vi tri bat dau cua cac canh hai phan trong mang edges
    int bipartiteStart = mcmf.edges.size();

    // Them cac canh hai phan (Shipper -> Don hang)
    for (int i = 0; i < m; i++) {
        auto [u, v, w] = edgeList[i];
        if (color[u] == 0) {
            mcmf.addEdge(u, v, 1, w);
        } else {
            mcmf.addEdge(v, u, 1, w);
        }
    }

    // ===== BUOC 3: Giai Min-Cost Max-Flow =====
    auto [maxMatching, minWeight] = mcmf.solve(S, T);

    // ===== BUOC 4: Xuat ket qua =====
    cout << maxMatching << " " << minWeight << endl;

    // Tim cac canh duoc chon trong bo ghep
    for (int i = 0; i < m; i++) {
        int edgeIdx = bipartiteStart + 2 * i; // Chi so cua canh thuan trong mang edges
        if (mcmf.edges[edgeIdx].flow > 0) {
            auto [u, v, w] = edgeList[i];
            cout << u << " " << v << endl;
        }
    }

    return 0;
}
