#include <bits/stdc++.h>
using namespace std;

/*
💡 Approach:
1. We are given a linked list and an array `nums`. 
   We need to delete all nodes from the linked list whose values are present in `nums`.

2. First, we store all the elements of `nums` into an unordered_set `st` 
   so that checking if a value exists becomes very fast (O(1)).

3. Then, we handle the case where the head itself needs to be deleted:
   - While the current head’s value is in the set, move the head pointer forward.

4. After that, we traverse the rest of the linked list using two pointers:
   - `curr` → points to the current node.
   - `prev` → keeps track of the previous node.
   - If `curr->val` is not in the set, move both pointers forward.
   - If it *is* in the set, skip the node by linking `prev->next` to `curr->next`.

5. Finally, return the updated head pointer.

✅ This way, we remove all unwanted nodes in a single traversal.

⏱️ Time Complexity: O(N + M)
   - N = number of nodes in the linked list
   - M = number of elements in `nums`
   - Because we iterate through both once, and set lookups are O(1) on average.

💾 Space Complexity: O(M)
   - For storing all elements of `nums` in an unordered_set.
*/

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        // Step 1: Store nums elements in a set for quick lookup
        unordered_set<int> st(begin(nums), end(nums));

        // Step 2: Handle nodes to be deleted from the beginning
        while (head != nullptr && st.count(head->val)) {
            head = head->next;
        }

        // Step 3: Traverse and delete nodes present in the set
        ListNode* curr = head;
        ListNode* prev = nullptr;

        while (curr != nullptr) {
            if (st.count(curr->val)) {
                // Delete current node
                prev->next = curr->next;
            } else {
                // Move prev forward only if node not deleted
                prev = curr;
            }
            curr = curr->next;
        }

        return head;
    }
};
