/* 28.89%
 * 6.67%
 */
#include <stdbool.h>
#include <stdlib.h>

#define HASHSIZE 199

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct QNode {
	struct TreeNode *tnode;
	struct QNode *next;
};

struct LNode {
	int val;
	int count;
	struct LNode *next;
};

void enqueue(struct QNode **head, struct QNode **tail, struct TreeNode *tnode);
struct TreeNode *dequeue(struct QNode **head, struct QNode **tail);
int tsearch(struct TreeNode *root, int val);
int hashfind(struct LNode **table, int val);
void hashadd(struct LNode **table, int val, int count);
int hash(int);
struct LNode *nalloc(int val, int count, struct LNode *next);
void nfree(struct LNode *head);


/* breadth-first-search with binary search and hash table */
bool
findTarget(struct TreeNode* root, int k)
{
	if (k > 20000 || k < -20000) {
		return false;
	}

	struct LNode *table[HASHSIZE];
	for (int h = 0; h < HASHSIZE; h++) {
		table[h] = NULL;
	}
	struct QNode *head = NULL;
	struct QNode *tail = NULL;
	enqueue(&head, &tail, root);
	struct TreeNode *curr;
	while (head) {
		curr = dequeue(&head, &tail);
		int val = curr->val;
		int diff = k - val;
		int count = hashfind(table, diff);
		if (count < 0) {
			count = tsearch(root, diff);
			hashadd(table, diff, count);
		}
		if (diff == val && count > 1) {
			for (int h = 0; h < HASHSIZE; h++) {
				nfree(table[h]);
			}
			return true;
		} else if (diff != val && count > 0) {
			for (int h = 0; h < HASHSIZE; h++) {
				nfree(table[h]);
			}
			return true;
		}
		if (hashfind(table, val) < 0) {
			count = tsearch(root, val);
			hashadd(table, val, count);
		}

		if (curr->left) {
			enqueue(&head, &tail, curr->left);
		}
		if (curr->right) {
			enqueue(&head, &tail, curr->right);
		}
	}
	for (int h = 0; h < HASHSIZE; h++) {
		nfree(table[h]);
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


struct TreeNode *
dequeue(struct QNode **head, struct QNode **tail)
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


int
hashfind(struct LNode **table, int val)
{
	int h = hash(val);
	struct LNode *curr = table[h];
	while (curr) {
		if (curr->val == val) {
			return curr->count;
		}
		curr = curr->next;
	}
	return -1;
}


void
hashadd(struct LNode **table, int val, int count)
{
	struct LNode *new = (struct LNode *)malloc(sizeof(struct LNode));
	int h = hash(val);
	new->val = val;
	new->count = count;
	new->next = table[h];
	table[h] = new;
}


int
hash(int val)
{
	val %= HASHSIZE;
	val *= 33;
	val %= HASHSIZE;
	return (val < 0) ? val+HASHSIZE : val;
}


void
nfree(struct LNode *head)
{
	if (head) {
		nfree(head->next);
		free(head);
	} else {
		return;
	}
}
