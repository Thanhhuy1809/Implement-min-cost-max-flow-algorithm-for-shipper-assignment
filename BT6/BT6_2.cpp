/*
 * BT6 - Bai toan 2: Dinh tuyen bang thong toi da
 * Thuat toan: Dinic's Max-Flow + Path Decomposition (phan luong)
 *
 * Buoc 1: Chay Dinic tim luong cuc dai tu s den t
 * Buoc 2: Phan luong thanh cac duong di don (path decomposition)
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

int dinic_max_flow(int s, int t) {
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

    int N, M, s, t;
    cin >> N >> M >> s >> t;

    init_flow(N + 1); // nodes 1..N

    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }

    int total_flow = dinic_max_flow(s, t);
    cout << total_flow << endl;

    // ===== PATH DECOMPOSITION =====
    // Tinh luong tren moi canh thuan (forward edge o chi so chan)
    int num_edge_pairs = edges.size() / 2;
    vector<int> rem_flow(num_edge_pairs);
    for (int i = 0; i < num_edge_pairs; i++) {
        rem_flow[i] = edges[2 * i + 1].cap; // luong = cap cua canh nguoc
    }

    // Lap: tim duong tu s->t co luong > 0, trich ra
    vector<pair<int, vector<int>>> paths; // (flow, path_nodes)

    while (true) {
        // BFS tim duong tu s den t co remaining flow > 0
        vector<int> parent_eid(N + 1, -1);
        vector<bool> vis(N + 1, false);
        queue<int> q;
        q.push(s);
        vis[s] = true;
        bool found = false;

        while (!q.empty() && !found) {
            int u = q.front(); q.pop();
            for (int id : graph[u]) {
                if (id % 2 != 0) continue; // chi xet canh thuan
                int v = edges[id].to;
                if (!vis[v] && rem_flow[id / 2] > 0) {
                    vis[v] = true;
                    parent_eid[v] = id;
                    if (v == t) { found = true; break; }
                    q.push(v);
                }
            }
        }

        if (!found) break;

        // Truy vet va tim bottleneck
        int bottleneck = INF;
        int cur = t;
        while (cur != s) {
            int eid = parent_eid[cur];
            bottleneck = min(bottleneck, rem_flow[eid / 2]);
            cur = edges[eid ^ 1].to;
        }

        // Trich duong di va tru luong
        vector<int> path_nodes;
        cur = t;
        while (cur != s) {
            path_nodes.push_back(cur);
            int eid = parent_eid[cur];
            rem_flow[eid / 2] -= bottleneck;
            cur = edges[eid ^ 1].to;
        }
        path_nodes.push_back(s);
        reverse(path_nodes.begin(), path_nodes.end());

        paths.push_back({bottleneck, path_nodes});
    }

    // Xuat phan luong
    cout << paths.size() << endl;
    for (auto& [f, p] : paths) {
        cout << f << " " << p.size();
        for (int node : p) cout << " " << node;
        cout << endl;
    }

    return 0;
}
