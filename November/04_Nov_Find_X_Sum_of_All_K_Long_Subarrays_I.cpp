#include <bits/stdc++.h>
using namespace std;

/*
🎯 Problem: 3318. Find X-Sum of All K-Long Subarrays I

💡 Approach:
We are asked to find the "x-sum" for every subarray of length k.

📘 What is X-Sum?
1. Count how many times each number appears in the subarray.
2. Keep only the top x most frequent numbers.
   - If two numbers have the same frequency, choose the one with the *larger value*.
3. Multiply each number by its frequency and sum them all.

🧠 Plan:
We’ll use a **sliding window** of size k and a hash map (unordered_map) to track
the frequency of each number within the current window.

For each window:
- Use a **min-heap (priority queue)** to find the top x most frequent elements.
  - Push pairs of (frequency, element).
  - Keep the heap size ≤ x (pop smallest when needed).
- Then calculate the sum of (freq * val) for all elements in the heap.

After processing each window, slide forward by:
- Removing the outgoing element from the frequency map.
- Adding the incoming one.

✅ Key Insight:
Heap ensures we efficiently maintain top x frequent elements.
Sliding window ensures we reuse previous counts instead of recalculating everything.

⏱️ Time Complexity:
O(n * (k log k))
- For each of n elements, we may compute heap of up to k elements.

💾 Space Complexity:
O(k)
- For the frequency map and heap (since window size = k)
*/

class Solution {
public:
    typedef pair<int, int> P; // (frequency, element)

    // Helper function to find sum of top x frequent elements in the current window
    int findTopXSum(unordered_map<int, int>& mp, int x) {
        // Min-heap to keep top x elements
        priority_queue<P, vector<P>, greater<P>> pq;

        for (auto& it : mp) {
            pq.push({it.second, it.first});
            if (pq.size() > x)
                pq.pop(); // remove smallest frequency (or smallest value in tie)
        }

        int sum = 0;
        while (!pq.empty()) {
            int freq=pq.top().first;
            int val=pq.top().second;
            pq.pop();
            sum += freq * val;
        }

        return sum;
    }

    vector<int> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        unordered_map<int, int> mp; // frequency map
        vector<int> result;

        int i = 0, j = 0;

        // Sliding window
        while (j < n) {
            mp[nums[j]]++;

            if (j - i + 1 == k) { // window reached size k
                result.push_back(findTopXSum(mp, x));

                // remove the leftmost element before sliding
                mp[nums[i]]--;
                if (mp[nums[i]] == 0)
                    mp.erase(nums[i]);
                i++;
            }
            j++;
        }

        return result;
    }
};

int main() {
    Solution sol;

    // Example test case
    vector<int> nums = {1, 2, 3, 1, 2, 2, 3};
    int k = 3;
    int x = 2;

    vector<int> ans = sol.findXSum(nums, k, x);

    cout << "X-Sum of each subarray of length " << k << ":\n";
    for (int val : ans)
        cout << val << " ";
    cout << endl;

    return 0;
}
