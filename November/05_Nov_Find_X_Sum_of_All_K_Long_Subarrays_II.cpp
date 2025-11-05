#include <bits/stdc++.h>
using namespace std;

/*
💡 Problem:
You are given an array `nums` and integers `k` and `x`.

For each subarray of length `k`, you must find its "X-sum".

🔹 X-sum = sum of (value * frequency) for the top `x` most frequent elements.
If two elements have the same frequency, the element with the **bigger value** is more frequent.
If there are fewer than `x` distinct elements, take all of them.

Return an array containing the X-sum for every subarray of length `k`.

---

💡 Approach:
We use a **sliding window** and two **balanced sets** (ordered containers) to maintain
the top `x` most frequent elements efficiently.

1️⃣ Maintain a frequency map `mp` to count occurrences of elements.
2️⃣ Use two ordered sets:
    - `mainSet`: stores top `x` frequent (frequency, value) pairs.
    - `extraSet`: stores the rest of the elements.
3️⃣ When a new element enters the window:
    - If it already exists, remove its old (freq, value) from the set.
    - Update its frequency, and insert it back.
4️⃣ When a number leaves the window:
    - Remove its (freq, value), decrease frequency, and reinsert if still > 0.
5️⃣ Keep track of the current sum of top `x` elements (`sum` variable).
6️⃣ Each time the window size reaches `k`, record `sum` in the result.

This approach ensures efficient updates when the window slides.

---

✅ Example:
nums = [1, 2, 3, 1, 2], k = 3, x = 2

Window 1 → [1, 2, 3]
freq = {1:1, 2:1, 3:1}
Top 2 = (3,1), (2,1) → sum = 5

Window 2 → [2, 3, 1] → same sum = 5

---

⏱️ Time Complexity: O(n * log x)
   Each insert and erase in set takes O(log x), and each element is processed twice (enter + exit).

💾 Space Complexity: O(k)
   For frequency map and two sets containing at most k distinct elements.
*/

class Solution {
public:
    long long sum = 0; // Sum of top x frequent elements
    set<pair<int, int>> mainSet; // Top x (frequency, value)
    set<pair<int, int>> extraSet; // Remaining (frequency, value)

    // Insert a (frequency, value) pair into proper set and adjust sum
    void insertInSet(const pair<int, int>& p, int x) {
        if (mainSet.size() < x || p > *mainSet.begin()) {
            sum += 1LL * p.first * p.second;
            mainSet.insert(p);

            // If mainSet exceeds x, move smallest to extraSet
            if (mainSet.size() > x) {
                pair<int, int> smallest = *mainSet.begin();
                sum -= 1LL * smallest.first * smallest.second;
                mainSet.erase(smallest);
                extraSet.insert(smallest);
            }
        } else {
            extraSet.insert(p);
        }
    }

    // Remove a (frequency, value) pair and rebalance sets if needed
    void removeFromSet(const pair<int, int>& p, int x) {
        if (mainSet.find(p) != mainSet.end()) {
            sum -= 1LL * p.first * p.second;
            mainSet.erase(p);

            // Move the largest element from extraSet to mainSet if available
            if (!extraSet.empty()) {
                pair<int, int> largest = *extraSet.rbegin();
                extraSet.erase(largest);
                mainSet.insert(largest);
                sum += 1LL * largest.first * largest.second;
            }
        } else {
            extraSet.erase(p);
        }
    }

    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        sum = 0;
        vector<long long> result;
        unordered_map<int, int> mp; // frequency map

        int i = 0, j = 0;

        while (j < n) {
            // If number already exists, remove its previous state
            if (mp[nums[j]] > 0) {
                removeFromSet(make_pair(mp[nums[j]], nums[j]), x);
            }

            // Increase frequency and reinsert
            mp[nums[j]]++;
            insertInSet(make_pair(mp[nums[j]], nums[j]), x);

            // When window size == k
            if (j - i + 1 == k) {
                result.push_back(sum);

                // Remove the outgoing element
                removeFromSet(make_pair(mp[nums[i]], nums[i]), x);
                mp[nums[i]]--;

                if (mp[nums[i]] == 0) {
                    mp.erase(nums[i]);
                } else {
                    insertInSet(make_pair(mp[nums[i]], nums[i]), x);
                }

                i++;
            }

            j++;
        }

        return result;
    }
};
