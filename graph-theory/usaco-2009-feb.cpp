#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
  int N, M, K;
  cin >> N >> M >> K;

  vector<vector<array<int, 2>>> adjList(N + 1);
  while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    adjList[u].push_back({v, w});
    adjList[v].push_back({u, w});
  }

  vector<vector<int>> dist(N + 1, vector<int>(K + 1, INF));
  priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>>
      pq;
  pq.push({0, 1, 0}); // dist, node id, k count
  dist[1][0] = 0;
  while (!pq.empty()) {
    int d = pq.top()[0], u = pq.top()[1], k = pq.top()[2];
    pq.pop();
    if (d > dist[u][k])
      continue;

    for (auto e : adjList[u]) {
      int v = e[0], w = e[1];
      // case-1: use the edge
      if (dist[v][k] > d + w) {
        dist[v][k] = d + w;
        pq.push({d + w, v, k});
      }

      // case-2: convert edge to zero
      if (k < K && dist[v][k + 1] > d + 0) {
        dist[v][k + 1] = d + 0;
        pq.push({d + 0, v, k + 1});
      }
    }
  }

  cout << *min_element(dist[N].begin(), dist[N].end()) << endl;
}