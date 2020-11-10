/* 68.89%
 * 6.67%
 */

#include <stdbool.h>
#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct QNode {
	struct TreeNode *tnode;
	struct QNode *next;
};

void enqueue(struct QNode **head, struct QNode **tail, struct TreeNode *tnode);
struct TreeNode *dequeue(struct QNode **head, struct QNode **tail);
int tsearch(struct TreeNode *root, int val);


/* breadth-first-search with binary search */
bool
findTarget(struct TreeNode* root, int k)
{
	if (k > 20000 || k < -20000) {
		return false;
	}

	struct QNode *head = NULL;
	struct QNode *tail = NULL;
	enqueue(&head, &tail, root);
	struct TreeNode *curr;
	while (head) {
		curr = dequeue(&head, &tail);
		int diff = k - curr->val;
		int count = tsearch(root, diff);
		if (diff == curr->val && count > 1) {
			return true;
		} else if (diff != curr->val && count > 0) {
			return true;
		}


		if (curr->left) {
			enqueue(&head, &tail, curr->left);
		}
		if (curr->right) {
			enqueue(&head, &tail, curr->right);
		}
	}
	return false;
}


int
tsearch(struct TreeNode *root, int val)
{
	if (root == NULL) {
		return 0;
	}
	if (val < root->val) {
		return tsearch(root->left, val);
	} else if (val > root->val) {
		return tsearch(root->right, val);
	} else {
		return 1 + tsearch(root->left, val) + tsearch(root->right, val);
	}
}


void
enqueue(struct QNode **head, struct QNode **tail, struct TreeNode *tnode)
{
	if (*head) {
		(*tail)->next = (struct QNode *)malloc(sizeof(struct QNode));
		*tail = (*tail)->next;
		(*tail)->tnode = tnode;
		(*tail)->next = NULL;
	} else {
		*tail = (struct QNode *)malloc(sizeof(struct QNode));
		(*tail)->tnode = tnode;
		(*tail)->next = NULL;
		*head = *tail;
	}
}


struct TreeNode *dequeue(struct QNode **head, struct QNode **tail)
{
	struct TreeNode *tnode = NULL;
	if (*head && *head != *tail) {
		tnode = (*head)->tnode;
		struct QNode *temp = *head;
		*head = (*head)->next;
		free(temp);
	} else if (*head) {
		tnode = (*head)->tnode;
		free(*head);
		*head = *tail = NULL;
	}
	return tnode;
}
