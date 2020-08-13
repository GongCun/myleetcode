/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {

  private:
    unordered_map<Node*, Node*> visited;
    
  public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return node;
        
        if (visited.find(node) != visited.end())
            return visited[node];

        Node *n = new Node(node->val);
        visited[node] = n;

        for (auto& i: node->neighbors) {
            n->neighbors.push_back(cloneGraph(i));
        }

        return n;
    }
};
