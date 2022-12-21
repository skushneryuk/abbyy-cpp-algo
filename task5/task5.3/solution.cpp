#include <set>
#include <vector>
#include <cmath>

using namespace std;


class Solution {
    const int INF = 1 << 30;

    int MST(const vector<vector<int>>& G, const vector<vector<int>>& edges, int ignore_edge=-1) {
        auto n = G.size();
        set<pair<int, int>> closest;
        vector<int> result(n, INF);
        vector<char> used(n, 0);

        closest.insert(make_pair(0, 0));
        int answer = 0;
        for (int k = 0; k < n; ++k) {
            auto [dist2MST, u] = *closest.begin();

            closest.erase(make_pair(dist2MST, u));
            used[u] = true;
            result[u] = 0;
            answer += dist2MST;

            for (auto edge_idx : G[u]) {
                auto v = edges[edge_idx][0];
                if (v == u) {
                    v = edges[edge_idx][1];
                }
                auto new_dist = edges[edge_idx][2];
                if (used[v] == 0 && result[v] > new_dist && edge_idx != ignore_edge) {
                    closest.erase(make_pair(result[v], v));
                    result[v] = new_dist;
                    closest.insert(make_pair(result[v], v));
                }
            }
        }
        return answer;
    }
    
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<vector<int>> G(n);
        vector<int> result(edges.size(), 0);

        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i][0];
            int v = edges[i][1];

            G[u].push_back(i);
            G[v].push_back(i);
        }

        auto real_mst = MST(G, edges);

        for (int i = 0; i < edges.size(); ++i) {
            if (MST(G, edges, i) != real_mst) {
                result[i] = 2;
            } else {
                auto old_edge = edges[i][2];
                edges[i][2] = 0;
                if (MST(G, edges) + old_edge == real_mst) {
                    result[i] = 1;
                }
                edges[i][2] = old_edge;
            }
        }

        vector<int> critical, pseudo;
        for (int i = 0; i < edges.size(); ++i) {
            if (result[i] == 1) {
                pseudo.push_back(i);
            }
            if (result[i] == 2) {
                critical.push_back(i);
            }
        }
        return {critical, pseudo};
    }
};