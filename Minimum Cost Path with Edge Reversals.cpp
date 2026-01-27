// 3650. Minimum Cost Path with Edge Reversals

class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        typedef long long ll;
        const ll INF = 1e18;

        vector<vector<pair<int,int>>> adj(n), radj(n);

        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            radj[v].push_back({u, w}); // reverse graph
        }

        // dist[node][state]
        vector<vector<ll>> dist(n, vector<ll>(2, INF));
        priority_queue<tuple<ll,int,int>, vector<tuple<ll,int,int>>, greater<>> pq;

        dist[0][0] = 0;
        pq.push({0, 0, 0}); // cost, node, state

        while (!pq.empty()) {
            auto [cost, u, state] = pq.top();
            pq.pop();

            if (cost > dist[u][state]) continue;

            // Normal edges
            for (auto [v, w] : adj[u]) {
                if (dist[v][0] > cost + w) {
                    dist[v][0] = cost + w;
                    pq.push({dist[v][0], v, 0});
                }
            }

            // Reverse edges using switch (only once)
            if (state == 0) {
                for (auto [v, w] : radj[u]) {
                    if (dist[v][1] > cost + 2LL * w) {
                        dist[v][1] = cost + 2LL * w;
                        pq.push({dist[v][1], v, 1});
                    }
                }
            }
        }

        ll ans = min(dist[n-1][0], dist[n-1][1]);
        return (ans == INF ? -1 : (int)ans);
    }
};
