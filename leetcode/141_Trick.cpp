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
		if (head == NULL) return false;
		ListNode *u1 = head, *u2 = head;
		do
		{
			u1 = u1->next;
			u2 = (u2->next == NULL ? NULL : u2->next->next);
			if (u2 == NULL) return false;
			if (u1 == u2) return true;
		} while (true);
	}
};
