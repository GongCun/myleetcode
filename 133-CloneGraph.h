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
    map<int, bool> visited;
    
    void explore(Node *node, Node *n) {
        visited[node->val] = true;
        n->val = node->val;
        /* cout << node->val << endl; */
        for (vector<Node*>::iterator it = node->neighbors.begin(); it != node->neighbors.end(); ++it) {
            if (!visited[(*it)->val]) {
                Node *n2 = new Node();
                n->neighbors.push_back(n2);
                explore(*it, n2);
            }
        }
    }

  public:
    Node* cloneGraph(Node* node) {
        Node *n = new Node();
        explore(node, n);

        return n;
    }
};
