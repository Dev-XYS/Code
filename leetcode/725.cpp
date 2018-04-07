// Problem Name: Split Linked List in Parts

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *         int val;
 *         ListNode *next;
 *         ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
	ListNode* create(ListNode *u, int l) {
		if (l == 0) return u;
		ListNode *prev = u, *res = u->next;
		for (int i = 1; i < l; i++)
		{
			prev = res;
			res = res->next;
		}
		prev->next = NULL;
		return res;
	}

	vector<ListNode*> splitListToParts(ListNode *root, int k) {
		int n = 0;
		for (ListNode *u = root; u != NULL; u = u->next)
		{
			n++;
		}
		vector<ListNode*> ans;
		ListNode *u = root;
		for (int c = 0; c < k; c++)
		{
			ans.push_back(u);
			u = create(u, c < n % k ? n / k + 1 : n / k);
		}
		return ans;
	}
};
