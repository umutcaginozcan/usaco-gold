// https://usaco.org/index.php?page=viewproblem2&cpid=969&lang=en

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;
// ifstream cin("pump.in");
// ofstream cout("pump.out");
const int INF = 1e9;

int main() {
  int N, M;
  cin >> N >> M;

  vector<vector<array<int, 3>>> adj_list(N + 1);
  while (M--) {
    int u, v, c, f;
    cin >> u >> v >> c >> f;
    adj_list[u].push_back({v, c, f});
    adj_list[v].push_back({u, c, f});
  }

  priority_queue<array<int, 4>, vector<array<int, 4>>, greater<array<int, 4>>>
      pq;
  vector<int> ratio(N + 1, INF); // want to minimize this
  ratio[1] = 0;                  // src
  pq.push({0, 0, INF, 1});       // {ratio, total cost, min-f, src}
  while (!pq.empty()) {
    int r = pq.top()[0], c = pq.top()[1], min_f = pq.top()[2], u = pq.top()[3];
    pq.pop();

    for (auto a : adj_list[u]) { // a: {node, cost to get there, flow}
      int v = a[0];
      int nc = c + a[1];
      int nf = min(min_f, a[2]);
      int nr = (int)(nc / nf * 1e6);

      if (nr > ratio[v])
        continue;

      pq.push({nr, nc, nf, v});
      ratio[v] =
          nr; // TODO: currently ratio holds cost / flow, should be changed
    }
  }

  cout << ratio[N] << endl;
}
