// https://usaco.org/index.php?page=viewproblem2&cpid=98

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int N, M;

int find_sp(vector<vector<array<int, 2>>> &adj_list, vector<int> &dist,
            vector<int> &pnt) {
  priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>>
      pq;
  pq.push({0, 1}); // {weight, node} — ağırlık önce olmalı, min-heap ağırlığa
                   // göre sıralar
  while (!pq.empty()) {
    int w = pq.top()[0], u = pq.top()[1];
    pq.pop();

    if (w > dist[u])
      continue; // stale entry, atla

    for (auto &n : adj_list[u]) {
      if (dist[n[0]] > dist[u] + n[1]) {
        dist[n[0]] = dist[u] + n[1];
        pnt[n[0]] = u;
        pq.push({dist[n[0]], n[0]});
      }
    }
  }
  return dist[N];
}

int main() {
  cin >> N >> M;

  vector<vector<array<int, 2>>> adj_list(N + 1);
  while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    adj_list[u].push_back({v, w});
    adj_list[v].push_back({u, w});
  }

  vector<int> dist(N + 1, INF);
  dist[1] = 0;
  vector<int> pnt(N + 1, -1);
  int first_sp = find_sp(adj_list, dist, pnt);

  // Yol üzerindeki kenarları topla
  vector<array<int, 2>> path_edges;
  int cur = N;
  while (pnt[cur] != -1) {
    path_edges.push_back({pnt[cur], cur});
    cur = pnt[cur];
  }

  int max_increase = 0;
  for (auto &edge : path_edges) {
    int a = edge[0], b = edge[1];

    // a->b ve b->a kenarlarını iki katına çıkar
    for (auto &n : adj_list[a])
      if (n[0] == b) {
        n[1] *= 2;
        break;
      }
    for (auto &n : adj_list[b])
      if (n[0] == a) {
        n[1] *= 2;
        break;
      }

    // dist ve pnt'yi sıfırla, tekrar Dijkstra çalıştır
    fill(dist.begin(), dist.end(), INF);
    dist[1] = 0;
    fill(pnt.begin(), pnt.end(), -1);
    int new_sp = find_sp(adj_list, dist, pnt);

    max_increase = max(max_increase, new_sp - first_sp);

    // Kenarları eski haline getir
    for (auto &n : adj_list[a])
      if (n[0] == b) {
        n[1] /= 2;
        break;
      }
    for (auto &n : adj_list[b])
      if (n[0] == a) {
        n[1] /= 2;
        break;
      }
  }

  cout << max_increase << endl;
}