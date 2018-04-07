// Problem Name: Binary Tree Preorder Traversal

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
	vector<int> preorderTraversal(TreeNode* root) {
		TreeNode *S[1000];
		int status[1000];
		int sp = 0;
		vector<int> ans;
		S[sp] = root;
		status[sp++] = 0;
		while (sp > 0)
		{
			if (S[sp - 1] == NULL)
			{
				sp--;
				continue;
			}
			if (status[sp - 1] == 0)
			{
				status[sp - 1] = 1;
				ans.push_back(S[sp - 1]->val);
			}
			else if (status[sp - 1] == 1)
			{
				status[sp - 1] = 2;
				S[sp] = S[sp - 1]->left;
				status[sp++] = 0;
			}
			else
			{
				S[sp - 1] = S[sp - 1]->right;
				status[sp - 1] = 0;
			}
		}
		return ans;
	}
};
