/*
Dijkstra's Shortest Path Algorithm
*/
#include <bits/stdc++.h>
using namespace std;
#define INF 1000000

int main() {
  int n = 5;

  vector<vector<pair<int, int>>> adj(n);
  adj[0] = {{1, 2}, {2, 4}};
  adj[1] = {{0, 2}, {2, 1}, {3, 7}};
  adj[2] = {{0, 4}, {1, 1}, {4, 3}};
  adj[3] = {{1, 7}, {4, 1}};
  adj[4] = {{2, 3}, {3, 1}};

  int src = 0;
  vector<int> dist(n, INF);
  dist[src] = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push({0, src});

  while (!pq.empty()) {
    int cur_dist = pq.top().first;
    int cur_node = pq.top().second;
    pq.pop();

    for (auto &n : adj[cur_node]) {
      int node = n.first;
      int new_d = cur_dist + n.second;
      if (dist[node] > new_d) {
        pq.push({new_d, node});
        dist[node] = new_d;
      }
    }
  }

  int i = 0;
  for (auto d : dist) {
    cout << "Min cost from src:" << src;
    cout << " to node n:" << i++;
    cout << " is:" << d << endl;
  }
}