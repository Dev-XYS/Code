// Problem Name: Linked List Cycle

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
	bool hasCycle(ListNode *head) {
		set<ListNode*> S;
		for (ListNode *u = head; u != NULL; u = u->next)
		{
			if (S.count(u) > 0)
			{
				return true;
			}
			S.insert(u);
		}
		return false;
	}
};
