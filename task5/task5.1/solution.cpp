#include <vector>
#include <set>

using namespace std;

class Solution {
    const long long INF = 1LL << 40;
    
    vector<long long> min_path(int start, const vector<vector<pair<int, long long>>>& G) {
        vector<long long> result(G.size(), INF);
        set<pair<long long, int>> closest;
        closest.insert(make_pair(0, start));
        result[start] = 0;

        while(!closest.empty()) {
            auto [dist, u] = *closest.begin();
            closest.erase(make_pair(dist, u));

            for (const auto [v, edge] : G[u]) {
                if (result[v] > dist + edge) {
                    closest.erase(make_pair(result[v], v));
                    closest.insert(make_pair(dist + edge, v));
                    result[v] = dist + edge;
                }
            }
        }

        return result;
    }
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        vector<vector<pair<int, long long>>> G1(n), G2(n);

        for (auto edge : edges) {
            auto u = edge[0];
            auto v = edge[1];
            auto weight = edge[2];

            G1[u].push_back(make_pair(v, weight));
            G2[v].push_back(make_pair(u, weight));
        }

        auto closest2src1 = min_path(src1, G1);
        auto closest2src2 = min_path(src2, G1);
        auto closest2dest = min_path(dest, G2);

        long long answer = 3 * INF;

        for (int u = 0; u < n; ++u) {
            if (closest2src1[u] + closest2src2[u] + closest2dest[u] < answer) {
                answer = closest2src1[u] + closest2src2[u] + closest2dest[u];
            }
        }
        if (answer > INF) {
            answer = -1;
        }
        return answer;
    }
};