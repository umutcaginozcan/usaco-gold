/*
LC787 Cheapest Flights Within K Stops
*/
class Solution {
#define INF 10000
public:
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                        int k) {
    vector<int> dist(n, INF);
    dist[src] = 0;

    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>>
        pq;
    pq.push({0, src});
    while (k-- > -1 && !pq.empty()) {
      int cur_dist = pq.top()[0];
      int cur_node = pq.top()[1];
      pq.pop();

      for (auto flight : flights) {
        if (flight[0] != cur_node)
          continue;
        int next_node = flight[1];
        int cost = flight[2];
        if (dist[next_node] > cost + cur_dist) {
          dist[next_node] = cost + cur_dist;
          pq.push({dist[next_node], next_node});
        }
      }
    }

    if (dist[dst] == INF)
      return -1;
    return dist[dst];
  }
};