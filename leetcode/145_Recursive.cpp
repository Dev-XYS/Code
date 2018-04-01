/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *         int val;
 *         TreeNode *left;
 *         TreeNode *right;
 *         TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
	vector<int> ans;

	void dfs(TreeNode* u) {
		if (u != NULL)
		{
			dfs(u->left);
			dfs(u->right);
			ans.push_back(u->val);
		}
	}
	
	vector<int> postorderTraversal(TreeNode* root) {
		dfs(root);
		return ans;
	}
};
