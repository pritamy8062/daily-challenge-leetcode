#include <bits/stdc++.h>
using namespace std;

/*
💡 Problem: Power Grid Maintenance (LeetCode 3607)

We are given:
- `c` power stations labeled from 1 to c.
- A list of bidirectional connections between them.
- A list of queries of two types:
    1️⃣ Query [1, node] → Return the smallest-numbered active station in the same connected component as `node`.
    2️⃣ Query [2, node] → Shut down the given node (remove it from the network).

We need to process all queries in order and return the result for type 1 queries.

---

💡 Approach: DFS + Component Grouping

1️⃣ Build an adjacency list from the given connections.
2️⃣ Use **DFS** to find all connected components.
    - Each component is assigned a unique `id`.
    - Maintain:
        - `nodeId[node]` → component ID of each node.
        - `mp[id]` → set of active nodes in that component.
3️⃣ When processing queries:
    - Type 1: 
        - If the queried node is still active, return it.
        - Otherwise, return the smallest active node in that component (from `set`).
        - If the component is empty, return -1.
    - Type 2:
        - Remove the node from its component’s set (deactivate it).
4️⃣ Use a `set<int>` for each component to efficiently:
    - Get smallest node (`O(log c)`)
    - Delete node (`O(log c)`)

---

✅ Example:
c = 4
connections = [[1,2],[2,3]]
queries = [[1,1],[2,2],[1,1]]

→ Components:
   {1,2,3}, {4}

After removing 2:
   Component {1,3}

Results: [1, 1]

---

⏱️ Time Complexity:
- Building graph + DFS: O(c + n)
- Processing queries: O(q * log c)
Overall → O((c + n) + q log c)

💾 Space Complexity:
- Graph, nodeId, and visited arrays → O(c + n)
- Component sets storage → O(c)
Overall → O(c + n)
*/

class Solution {
public:
    // DFS to mark nodes of same connected component
    void dfs(int node, unordered_map<int, vector<int>>& adj, int id, vector<int>& nodeId, 
             unordered_map<int, set<int>>& mp, vector<bool>& visited) {
        visited[node] = true;
        mp[id].insert(node);
        nodeId[node] = id;

        for (int ngbr : adj[node]) {
            if (!visited[ngbr]) {
                dfs(ngbr, adj, id, nodeId, mp, visited);
            }
        }
    }

    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        unordered_map<int, vector<int>> adj;

        // Build adjacency list
        for (int i = 0; i < (int)connections.size(); i++) {
            int u = connections[i][0];
            int v = connections[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<bool> visited(c + 1, false);
        vector<int> nodeId(c + 1);
        unordered_map<int, set<int>> mp; // component id -> set of active nodes

        // Step 1: Find all connected components
        for (int node = 1; node <= c; node++) {
            if (!visited[node]) {
                int id = node; // use the node itself as component id
                dfs(node, adj, id, nodeId, mp, visited);
            }
        }

        // Step 2: Process queries
        vector<int> result;
        for (int i = 0; i < (int)queries.size(); i++) {
            int type = queries[i][0];
            int node = queries[i][1];
            int id = nodeId[node];

            if (type == 1) {
                if (mp[id].count(node)) {
                    result.push_back(node);
                } else if (!mp[id].empty()) {
                    result.push_back(*mp[id].begin()); // smallest active node
                } else {
                    result.push_back(-1);
                }
            } else { 
                // type == 2 → deactivate this node
                mp[id].erase(node);
            }
        }

        return result;
    }
};
