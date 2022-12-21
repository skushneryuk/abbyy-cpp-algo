#include <queue>
#include <stdexcept>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        auto n = edges.size();
        vector<int> out_cnt(n, 0);
        vector<vector<int>> parents(n);

        auto two_parent_u = -1;

        // считаем in и out степени вершины
        for (const auto& edge : edges) {
            ++out_cnt[edge[0] - 1];
            parents[edge[1] - 1].push_back(edge[0] - 1);
            if (parents[edge[1] - 1].size() > 1) {
                two_parent_u = edge[1] - 1;
            }
        }

        // обрезаем листья
        queue<int> leaves;
        for (int u = 0; u < n; ++u) {
            if (out_cnt[u] == 0) {
                leaves.push(u);
            }
        }

        while (!leaves.empty()) {
            auto u = leaves.front();
            leaves.pop();

            if (u == two_parent_u) {
                return {parents[u][1] + 1, u + 1};
            }

            if (--out_cnt[parents[u][0]] == 0) {
                leaves.push(parents[u][0]);
            }
        }

        // остался цикл
        if (two_parent_u == -1) {
            for (int i = edges.size() - 1; i >= 0; --i) {
                if (out_cnt[edges[i][0] - 1] != 0 && out_cnt[edges[i][1] - 1] != 0) {
                    return edges[i];
                }
            }
        } else {  // лассо
            // auto prev = two_parent_u;
            auto prev = parents[two_parent_u][0];
            while (parents[prev].size() != 0 && parents[prev][0] != two_parent_u) {
                prev = parents[prev][0];
            }
            if (parents[prev].size() == 0) {
                return {parents[two_parent_u][1] + 1, two_parent_u + 1};
            }
            if (parents[prev][0] == two_parent_u) {
                return {parents[two_parent_u][0] + 1, two_parent_u + 1};
            }
        }

        throw invalid_argument("Invalid argument edges: no redundant connection found");
    }
};