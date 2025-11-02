#include <bits/stdc++.h>
using namespace std;

/*
💡 Approach:
We are given a grid with guards and walls. 
A guard can watch (or "guard") all cells in its row and column until blocked by another guard or a wall.
We need to count how many cells are NOT guarded by anyone.

Steps:
1. Create a grid of size m x n, initially filled with 0.
   - 0 → empty cell
   - 1 → guarded cell
   - 2 → guard
   - 3 → wall

2. Mark all guard positions (2) and wall positions (3).

3. For each guard:
   - Move in all 4 directions (up, down, left, right)
   - Mark every reachable cell as guarded (1) 
     until you hit another guard (2) or a wall (3).

4. Finally, count all cells that are still 0 — these are unguarded.

✅ Efficient because we only mark each direction until blocked.

⏱️ Time Complexity: O(m * n)
   - Each cell is visited at most a few times while marking.

💾 Space Complexity: O(m * n)
   - For storing the grid.
*/

class Solution {
public:
    void markGuarded(int row, int col, vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // UP
        for (int i = row - 1; i >= 0; i--) {
            if (grid[i][col] == 2 || grid[i][col] == 3)
                break;
            grid[i][col] = 1;
        }

        // DOWN
        for (int i = row + 1; i < m; i++) {
            if (grid[i][col] == 2 || grid[i][col] == 3)
                break;
            grid[i][col] = 1;
        }

        // LEFT
        for (int j = col - 1; j >= 0; j--) {
            if (grid[row][j] == 2 || grid[row][j] == 3)
                break;
            grid[row][j] = 1;
        }

        // RIGHT
        for (int j = col + 1; j < n; j++) {
            if (grid[row][j] == 2 || grid[row][j] == 3)
                break;
            grid[row][j] = 1;
        }
    }

    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>> grid(m, vector<int>(n, 0));

        // Mark guard positions
        for (auto& g : guards)
            grid[g[0]][g[1]] = 2;

        // Mark wall positions
        for (auto& w : walls)
            grid[w[0]][w[1]] = 3;

        // Mark guarded cells for each guard
        for (auto& g : guards)
            markGuarded(g[0], g[1], grid);

        // Count unguarded cells
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0)
                    count++;
            }
        }

        return count;
    }
};
