/*
Bellman-Ford Shortest Path Algorithm
*/
#include <bits/stdc++.h>
using namespace std;
#define INF 1000000

int main() {
  int n = 3;

  // {from, to, weight}
  vector<tuple<int, int, int>> edges = {
      {0, 1, 1}, {1, 2, 1}, {2, 1, -3} // Negative cycle.
  };

  int src = 0;
  vector<int> dist(n, INF);
  dist[src] = 0;

  // V-1 iteration
  for (int i = 0; i < n - 1; i++) {
    for (auto &[from, to, w] : edges) {
      int cost = dist[from] + w;
      if (dist[to] > cost) {
        dist[to] = cost;
      }
    }
  }

  // Negatif cycle detection
  bool negative_cycle = false;
  for (auto &[from, to, w] : edges) {
    int cost = dist[from] + w;
    if (dist[to] > cost) {
      dist[to] = cost;
      negative_cycle = true;
    }
  }

  if (negative_cycle) {
    cout << "Negative cycle detected!" << endl;
    return 1;
  }

  int i = 0;
  for (auto d : dist) {
    cout << "Min cost from src:" << src;
    cout << " to node n:" << i++;
    cout << " is:" << d << endl;
  }
}