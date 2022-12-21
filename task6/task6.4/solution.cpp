#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> G;
    vector<int> tin;  // both tin and used
    vector<int> fup;
    vector<vector<int>> answer;
    int timer = 0;

    void dfs(int u, int parent) {
        tin[u] = fup[u] = ++timer;

        for (auto v : G[u]) {
            if (v == parent)  {
                continue;
            }
            if (tin[v] > 0) {
                fup[u] = min(fup[u], tin[v]);
            }
            else {
                dfs(v, u);
                fup[u] = min(fup[u], fup[v]);
                if (fup[v] > tin[u]) {
                    answer.push_back({u, v});
                }
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        G = vector<vector<int>>(n);
        tin = vector<int>(n, -1);
        fup = vector<int>(n, n + 1);
        timer = 0;

        for (auto edge: connections) {
            G[edge[0]].push_back(edge[1]);
            G[edge[1]].push_back(edge[0]);
        }
        dfs(0, -1);
        
        return answer;
    }
};