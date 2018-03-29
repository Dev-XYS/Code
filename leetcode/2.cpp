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
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode *ans = new ListNode(0), *cur = ans;
		int carry = 0;
		while (true)
		{
			carry = l1->val + l2->val + carry;
			cur->val = carry % 10;
			carry /= 10;
			l1 = l1->next;
			l2 = l2->next;
			if (l1 == NULL && l2 == NULL)
			{
				break;
			}
			if (l1 == NULL)
			{
				l1 = new ListNode(0);
			}
			else if (l2 == NULL)
			{
				l2 = new ListNode(0);
			}
			cur = (cur->next = new ListNode(0));
		}
		if (carry > 0)
		{
			cur->next = new ListNode(carry);
		}
		return ans;
	}
};
