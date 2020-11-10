/* 24 ms
 * 25.00%
 * 75.00%
 */
#include <stdbool.h>
#include <stdlib.h>

#define HSIZE 101

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct qnode {
	struct TreeNode *val;
	struct qnode *next;
};

typedef struct qnode QNode;

void enqueue(QNode **head, QNode **tail, struct TreeNode *val);
struct TreeNode *dequeue(QNode **head, QNode **tail);
void Qfree(QNode *node);

int hash(int);

struct lnode {
	int val;
	struct lnode *next;
};

typedef struct lnode LNode;

bool search(struct TreeNode *root, LNode **table, int val);
void Lfree(LNode *node);


/* BFS on tree1 and Hash Table on tree2 */
bool
twoSumBSTs(struct TreeNode* root1, struct TreeNode* root2, int target)
{
	QNode *head = NULL;
	QNode *tail = NULL;
	enqueue(&head, &tail, root1);

	LNode **table = (LNode **)calloc(HSIZE, sizeof(LNode *));
	struct TreeNode *curr;
	while (head) {
		curr = dequeue(&head, &tail);
		if (search(root2, table, target - curr->val)) {
			Qfree(head);
			for (int h = 0; h < HSIZE; h++) {
				Lfree(table[h]);
			}
			return true;
		}
		if (curr->left) {
			enqueue(&head, &tail, curr->left);
		}
		if (curr->right) {
			enqueue(&head, &tail, curr->right);
		}
	}
	Qfree(head);
	for (int h = 0; h < HSIZE; h++) {
		Lfree(table[h]);
	}
	return false;
}


void
enqueue(QNode **head, QNode **tail, struct TreeNode *val)
{
	if (*head) {
		(*tail)->next = (QNode *)malloc(sizeof(QNode));
		*tail = (*tail)->next;
		(*tail)->val = val;
		(*tail)->next = NULL;
	} else {
		(*tail) = (QNode *)malloc(sizeof(QNode));
		(*tail)->val = val;
		(*tail)->next = NULL;
		*head = *tail;
	}
}


struct TreeNode *
dequeue(QNode **head, QNode **tail)
{
	if (*head) {
		struct TreeNode *val = (*head)->val;
		QNode *temp = *head;
		if (*head != *tail) {
			(*head) = (*head)->next;
		} else {
			*head = *tail = NULL;
		}
		free(temp);
		return val;
	} else {
		return NULL;
	}
}


void
Qfree(QNode *node)
{
	if (node) {
		Qfree(node->next);
		free(node);
	} else {
		return;
	}
}


int
hash(int val)
{
	val %= HSIZE;
	val *= 33;
	val %= HSIZE;
	return (val < 0) ? val + HSIZE : val;
}


/* hash table records values NOT present */
bool
search(struct TreeNode *root, LNode **table, int val)
{
	int h = hash(val);
	LNode *curr;
	/* check table */
	for (curr = table[h]; curr; curr = curr->next) {
		if (curr->val == val) {
			return false;
		}
	}
	/* binary search */
	while (root) {
		if (root->val > val) {
			root = root->left;
		} else if (root->val < val) {
			root = root->right;
		} else {
			return true;
		}
	}
	/* add value to table */
	curr = (LNode *)malloc(sizeof(LNode));
	curr->val = val;
	curr->next = table[h];
	table[h] = curr;
	return false;
}


void
Lfree(LNode *node)
{
	if (node) {
		Lfree(node->next);
		free(node);
	} else {
		return;
	}
}
