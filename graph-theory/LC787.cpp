/*
LC787 Cheapest Flights Within K Stops
*/
class Solution {
public:
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                        int k) {

    vector<vector<array<int, 2>>> adjList(n);
    for (auto e : flights) {
      int u = e[0], v = e[1], w = e[2];
      adjList[u].push_back({v, w});
    }

    vector<vector<int>> dist(n, vector<int>(k + 2, 1e6));
    dist[src][0] = 0;

    // dist, node id, k
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>>
        pq;
    pq.push({0, src, 0});

    while (!pq.empty()) {
      int d = pq.top()[0];
      int u = pq.top()[1];
      int cnt = pq.top()[2];
      pq.pop();

      if (cnt == k + 1)
        continue;
      if (d > dist[u][cnt])
        continue;

      for (auto e : adjList[u]) {
        int v = e[0], w = e[1];

        if (dist[v][cnt + 1] > dist[u][cnt] + w) {
          dist[v][cnt + 1] = dist[u][cnt] + w;
          pq.push({dist[v][cnt + 1], v, cnt + 1});
        }
      }
    }

    int ans = *min_element(dist[dst].begin(), dist[dst].end());
    return ans == 1e6 ? -1 : ans;
  }
};