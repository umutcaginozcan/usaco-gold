/*
Floyd-Warshall All-Pairs Shortest Path Algorithm

DP over intermediate nodes k.
Recurrence: dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
Negative cycle detection: dist[i][i] < 0 after completion.
*/
#include <bits/stdc++.h>
using namespace std;
#define INF 1000000

int main() {
  int n = 4;

  // {from, to, weight}
  vector<tuple<int, int, int>> edges = {
      {0, 1, 3}, {0, 3, 7}, {1, 0, 8}, {1, 2, 2},
      {2, 0, 5}, {2, 3, 1}, {3, 0, 2} // Negative cycle test: uncomment below
                                      // {0, 1, 1}, {1, 2, 1}, {2, 0, -5}
  };

  // Init distance matrix
  vector<vector<int>> dist(n, vector<int>(n, INF));
  for (int i = 0; i < n; i++)
    dist[i][i] = 0;
  for (auto &[from, to, w] : edges)
    dist[from][to] = w;

  // Floyd-Warshall: try every intermediate node k
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (dist[i][k] != INF && dist[k][j] != INF)
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

  // Negative cycle detection: any dist[i][i] < 0
  for (int i = 0; i < n; i++) {
    if (dist[i][i] < 0) {
      cout << "Negative cycle detected!" << endl;
      return 1;
    }
  }

  // Print all-pairs result
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cout << "Min cost from " << i << " to " << j
           << " is: " << (dist[i][j] == INF ? -1 : dist[i][j]) << endl;
}