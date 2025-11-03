#include <bits/stdc++.h>
using namespace std;

/*
🎯 Problem: 1578. Minimum Time to Make Rope Colorful

💡 Approach:
We have a rope with balloons of different colors.
If two adjacent balloons have the same color, one must be removed.
To minimize total time, we should always remove the balloon
that takes *less time* to remove (the cheaper one).

So, for every sequence of consecutive same-colored balloons:
→ Keep the one with the highest removal time.
→ Add the removal time of all others to the total.

✅ Greedy Strategy:
At each step, add the minimum of (current balloon time, previous max time)
and keep updating the previous max.

🧩 Example:
colors = "abaac"
neededTime = [1,2,3,4,5]

→ Between the two 'a's (indices 2,3): remove the one with less time (3)
Total time = 3

⏱️ Time Complexity: O(n)
   - We iterate through all balloons once.

💾 Space Complexity: O(1)
   - Only a few integer variables are used.
*/

class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();
        int totalTime = 0;
        int prevMax = 0; // maximum removal time in current color group

        for (int i = 0; i < n; i++) {
            // if color changes, reset previous max
            if (i > 0 && colors[i] != colors[i - 1])
                prevMax = 0;

            int curr = neededTime[i];
            totalTime += min(prevMax, curr); // remove the cheaper balloon
            prevMax = max(prevMax, curr);    // keep the costlier one
        }

        return totalTime;
    }
};
