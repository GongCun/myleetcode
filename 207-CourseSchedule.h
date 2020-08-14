/* https://www.geeksforgeeks.org/detect-cycle-in-a-graph/ */
class Solution {
  private:
    bool isCyclicUtil(int v, vector<vector<int>>& adj,
                      vector<bool>& visited, vector<bool>& stacked) {
        if (!visited[v]) {
            visited[v] = true;
            stacked[v] = true;

            for (auto& i: adj[v]) {
                if (!visited[i] && isCyclicUtil(i, adj, visited, stacked))
                    return true;
                else if (stacked[i])
                    return true;
            }
        }
        stacked[v] = false;
        return false;
    }
    
  public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<bool> visited(numCourses, false);
        vector<bool> stacked(numCourses, false);
        
        for (int i = 0; i < prerequisites.size(); ++i) {
            adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }

        for (int i = 0; i < numCourses; ++i) {
            if (isCyclicUtil(i, adj, visited, stacked))
                return false;
        }

        return true;
    }
};
