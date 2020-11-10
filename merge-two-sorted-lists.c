#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 * int val;
 * struct ListNode *next;
 * };
 */


struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
	if (l1 == NULL) {
		return l2;
	} else if (l2 == NULL) {
		return l1;
	}

	struct ListNode *head = (struct ListNode*)malloc(sizeof(struct ListNode));
	struct ListNode *curr = head;

	while (l1 != NULL && l2 != NULL) {
		if (l1->val < l2->val) {
			curr->next = l1;
			l1 = l1->next;
		} else {
			curr->next = l2;
			l2 = l2->next;
		}
		curr = curr->next;
	}

	if (l1 == NULL) {
		curr->next = l2;
	} else {
		curr->next = l1;
	}

	curr = head;
	head = head->next;
	free(curr);
	return head;
}
