/*
// Definition for a Node.
class Node {
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};
*/

class Solution {
public:
	vector<int> preorder(Node* root) {
		if (root == nullptr) {
			return vector<int>();
		}
		vector<int> r = { root->val };
		for (auto u : root->children) {
			vector<int> t = preorder(u);
			r.insert(r.end(), t.begin(), t.end());
		}
		return r;
	}
};