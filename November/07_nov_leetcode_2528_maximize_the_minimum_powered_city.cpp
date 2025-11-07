#include <bits/stdc++.h>
using namespace std;

/*
----------------------------------------------
🧩 Problem: Leetcode 2528 - Maximize the Minimum Powered City
----------------------------------------------

🎯 Goal:
You are given `n` cities with some existing power stations.
Each station at index `i` powers all cities within distance `r` (inclusive).

You can build at most `k` additional power stations anywhere.
Return the **maximum possible minimum power** among all cities after placing up to `k` stations.

----------------------------------------------
💡 Approach:
----------------------------------------------

✅ Step 1: Use a Difference Array
----------------------------------------------
- Normally, each station at index `i` adds power to all cities in range `[i - r, i + r]`.
- Instead of updating each city individually (O(n*r)), we use a **difference array** to handle
  range updates efficiently in O(1).
- Add +stations[i] at start index `(i - r)` and subtract at `(i + r + 1)`.

✅ Step 2: Binary Search on the Answer
----------------------------------------------
- We binary search the **minimum power** that every city can have (say `mid`).
- The search range is from the smallest initial power to total power + k.

✅ Step 3: Check Function (Greedy Validation)
----------------------------------------------
- For each guessed `mid`, we check if we can make all cities have ≥ `mid` power.
- If any city has less than `mid`, we “add” stations there greedily.
- Each new station also affects the next `(2*r + 1)` cities using the difference array technique.
- If we ever need more than `k` stations, it’s not possible.

✅ Step 4: Adjust Binary Search
----------------------------------------------
- If possible to achieve `mid`, search higher (increase left bound).
- Otherwise, search lower (decrease right bound).

----------------------------------------------
⏱️ Time Complexity: O(n * log(sum + k))
   - For each binary search step, we traverse all cities once.

💾 Space Complexity: O(n)
   - To store difference array and temporary prefix sums.
----------------------------------------------
*/

class Solution {
public:
    // Helper function to check if all cities can have power >= mid
    bool check(long long mid, vector<long long>& diff, int r, int k, int n) {
        vector<long long> tempDiff = diff;
        long long cumSum = 0; // current cumulative power

        for (int i = 0; i < n; i++) {
            cumSum += tempDiff[i];

            if (cumSum < mid) {
                long long need = mid - cumSum;
                if (need > k) return false; // not enough stations available

                k -= need;
                cumSum += need;

                // new station affects the range [i, i + 2*r]
                if (i + 2 * r + 1 < n)
                    tempDiff[i + 2 * r + 1] -= need;
            }
        }
        return true;
    }

    long long maxPower(vector<int>& stations, int r, int k) {
        int n = stations.size();
        vector<long long> diff(n, 0);

        // Build difference array for existing stations
        for (int i = 0; i < n; i++) {
            diff[max(0, i - r)] += stations[i];
            if (i + r + 1 < n)
                diff[i + r + 1] -= stations[i];
        }

        // Binary search on possible minimum power value
        long long left = *min_element(stations.begin(), stations.end());
        long long right = accumulate(stations.begin(), stations.end(), 0LL) + k;
        long long result = 0;

        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (check(mid, diff, r, k, n)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return result;
    }
};
