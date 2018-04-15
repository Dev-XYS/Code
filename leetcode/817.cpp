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
	int numComponents(ListNode* head, vector<int>& G) {
		static bool has[10010];
		memset(has, 0, sizeof(has));
		for (int i = 0; i < G.size(); i++)
		{
			has[G[i]] = true;
		}
		int ans = 0, cnt = 0;
		for (ListNode *u = head; u != NULL; u = u->next)
		{
			if (has[u->val])
			{
				cnt++;
			}
			else
			{
				if (cnt > 0)
				{
					ans++;
					cnt = 0;
				}
			}
		}
		if (cnt > 0) ans++;
		return ans;
	}
};
