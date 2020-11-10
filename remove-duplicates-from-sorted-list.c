#include <stdlib.h>


struct ListNode {
    int val;
    struct ListNode *next;
};



struct ListNode*
deleteDuplicates(struct ListNode* head)
{
	if (head == NULL) {
		return head;
	}

	struct ListNode *curr = head;
	struct ListNode *next = head->next;
	while (next != NULL) {
		if (curr->val != next->val) {
			curr->next = next;
			curr = next;
		} else {
			next = next->next;
		}
	}
	curr->next = NULL;

	return head;
}
