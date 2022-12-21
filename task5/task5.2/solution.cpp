#include <set>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
    const int INF = 1 << 30;

    int dist(const vector<vector<int>>& points, int idx1, int idx2) {
        return abs(points[idx1][0] - points[idx2][0]) + abs(points[idx1][1] - points[idx2][1]);
    }

public:
    int minCostConnectPoints(const vector<vector<int>>& points) {
        auto n = points.size();
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

            for (int v = 0; v < n; ++v) {
                auto new_dist = dist(points, u, v);
                if (used[v] == 0 && result[v] > new_dist) {
                    closest.erase(make_pair(result[v], v));
                    result[v] = new_dist;
                    closest.insert(make_pair(result[v], v));
                }
            }
        }
        return answer;
    }
};