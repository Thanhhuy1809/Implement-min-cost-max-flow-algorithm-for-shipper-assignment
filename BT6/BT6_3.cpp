/*
 * BT6 - Bai toan 3: Dieu phoi xe cuu thuong
 * Thuat toan: Dijkstra (duong di ngan nhat) + Kuhn's Algorithm (ghep cap hai phan cuc dai)
 *
 * Buoc 1: Chay Dijkstra tu moi xe cuu thuong, tinh khoang cach ngan nhat den moi nut
 * Buoc 2: Xay dung do thi hai phan: xe i co the phuc vu ca j neu dist[i][pos_j] <= deadline_j
 * Buoc 3: Tim ghep cap cuc dai bang thuat toan Kuhn (duong mo rong)
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
const int INF = 1e9;

// ===== DIJKSTRA =====
vector<int> dijkstra(int src, const vector<vector<pii>>& adj, int n) {
    vector<int> dist(n + 1, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ===== KUHN'S ALGORITHM (Ghep cap hai phan) =====
int A_count, P_count;
vector<vector<int>> bip_adj; // bip_adj[xe_i] = danh sach ca_j co the phuc vu
vector<int> match_patient;   // match_patient[j] = xe duoc ghep voi ca j (-1 neu chua ghep)
vector<bool> used;

bool try_kuhn(int v) {
    for (int to : bip_adj[v]) {
        if (!used[to]) {
            used[to] = true;
            if (match_patient[to] == -1 || try_kuhn(match_patient[to])) {
                match_patient[to] = v;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, A, P;
    cin >> N >> M >> A >> P;

    // Doc vi tri xe cuu thuong
    vector<int> amb_pos(A);
    for (int i = 0; i < A; i++) cin >> amb_pos[i];

    // Doc hien truong (vi tri, thoi gian toi da)
    vector<int> pat_pos(P), pat_deadline(P);
    for (int i = 0; i < P; i++) cin >> pat_pos[i] >> pat_deadline[i];

    // Doc do thi duong (vo huong)
    vector<vector<pii>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        adj[u].push_back({v, t});
        adj[v].push_back({u, t}); // vo huong
    }

    // ===== BUOC 1: Dijkstra tu moi xe =====
    vector<vector<int>> dist_from_amb(A);
    for (int i = 0; i < A; i++) {
        dist_from_amb[i] = dijkstra(amb_pos[i], adj, N);
    }

    // ===== BUOC 2: Xay dung do thi hai phan =====
    bip_adj.assign(A, {});
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < P; j++) {
            if (dist_from_amb[i][pat_pos[j]] <= pat_deadline[j]) {
                bip_adj[i].push_back(j);
            }
        }
    }

    // ===== BUOC 3: Ghep cap cuc dai (Kuhn) =====
    match_patient.assign(P, -1);
    int total_matched = 0;
    for (int i = 0; i < A; i++) {
        used.assign(P, false);
        if (try_kuhn(i)) total_matched++;
    }

    // ===== XUAT KET QUA =====
    cout << total_matched << endl;
    for (int j = 0; j < P; j++) {
        if (match_patient[j] != -1) {
            cout << match_patient[j] + 1 << " " << j + 1 << endl;
        }
    }

    return 0;
}
