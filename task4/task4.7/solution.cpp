#include <vector>

using namespace std;

class Solution {
public:
    bool dfs(const vector<vector<char>>& grid, vector<vector<int>>& visited, int x, int y, int count) {
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || visited[x][y] > 0 || grid[x][y] == '0') {
            return false;
        }

        visited[x][y] = count;
        dfs(grid, visited, x - 1, y, count);
        dfs(grid, visited, x + 1, y, count);
        dfs(grid, visited, x, y - 1, count);
        dfs(grid, visited, x, y + 1, count);
        return true;
    }

    int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
        auto m = grid.size();
        auto n = grid[0].size();
        vector<vector<int>> visited(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(grid, visited, i, j, ans + 1)) {
                    ++ans;
                }
            }
        }
        return ans;
    }
};