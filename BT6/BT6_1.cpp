/*
 * BT6 - Bai toan 1: Phan phoi Vac-xin
 * Thuat toan: Dinic's Max-Flow voi sieu nguon / sieu dich
 *
 * Mo hinh:
 *   Super_Source -> Kho_i (cap = supply_i)
 *   Kho -> Tram (cap = z, theo canh mang)
 *   Tram_j -> Super_Sink (cap = demand_j)
 */

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge { int to, cap; };

int N_NODES;
vector<Edge> edges;
vector<vector<int>> graph;
vector<int> dist_bfs, ptr_dfs;

void init_flow(int n) {
    N_NODES = n;
    graph.assign(n, {});
    edges.clear();
}

void add_edge(int from, int to, int cap) {
    graph[from].push_back(edges.size());
    edges.push_back({to, cap});
    graph[to].push_back(edges.size());
    edges.push_back({from, 0});
}

bool bfs(int s, int t) {
    dist_bfs.assign(N_NODES, -1);
    dist_bfs[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int id : graph[v]) {
            if (dist_bfs[edges[id].to] == -1 && edges[id].cap > 0) {
                dist_bfs[edges[id].to] = dist_bfs[v] + 1;
                q.push(edges[id].to);
            }
        }
    }
    return dist_bfs[t] != -1;
}

int dfs(int v, int t, int pushed) {
    if (v == t || pushed == 0) return pushed;
    for (int& cid = ptr_dfs[v]; cid < (int)graph[v].size(); cid++) {
        int id = graph[v][cid];
        int to = edges[id].to;
        if (dist_bfs[v] + 1 != dist_bfs[to] || edges[id].cap <= 0) continue;
        int tr = dfs(to, t, min(pushed, edges[id].cap));
        if (tr > 0) {
            edges[id].cap -= tr;
            edges[id ^ 1].cap += tr;
            return tr;
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        ptr_dfs.assign(N_NODES, 0);
        while (int pushed = dfs(s, t, INF))
            flow += pushed;
    }
    return flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, W, C;
    cin >> N >> M >> W >> C;

    int S = 0, T = N + 1;
    init_flow(N + 2);

    int totalDemand = 0;

    // Doc W kho (id, supply)
    for (int i = 0; i < W; i++) {
        int id, supply;
        cin >> id >> supply;
        add_edge(S, id, supply);
    }

    // Doc C tram y te (id, demand)
    for (int i = 0; i < C; i++) {
        int id, demand;
        cin >> id >> demand;
        add_edge(id, T, demand);
        totalDemand += demand;
    }

    // Doc M canh co huong
    for (int i = 0; i < M; i++) {
        int u, v, z;
        cin >> u >> v >> z;
        add_edge(u, v, z);
    }

    int result = max_flow(S, T);

    cout << result << endl;
    cout << (result >= totalDemand ? "YES" : "NO") << endl;

    return 0;
}
