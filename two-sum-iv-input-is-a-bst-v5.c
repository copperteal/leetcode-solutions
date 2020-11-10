/* 95.56%
 * 6.67%
 */
#include <stdbool.h>
#include <stdlib.h>

#define QUEUESIZE 16  /* set to 32 for consistent 80% */
#define HASHSIZE 199


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct HNode {
	int val;
	int count;
	struct HNode *next;
};

int tsearch(struct TreeNode *root, int val);
int hashfind(struct TreeNode *root, struct HNode **table, int val);
int hash(int);
void nfree(struct HNode *head);


/* breadth-first-search with binary search and hash table but array
*  * implementation of queue. */
bool
findTarget(struct TreeNode* root, int k)
{
	if (k > 20000 || k < -20000) {
		return false;
	}

	int h, i, j;
	struct HNode *table[HASHSIZE];
	for (h = 0; h < HASHSIZE; h++) {
		table[h] = NULL;
	}

	int len = QUEUESIZE;
	int head = 0;
	int tail = 0;
	struct TreeNode **queue = (struct TreeNode **)calloc(len, sizeof(struct TreeNode *));

	queue[tail++] = root;
	struct TreeNode *curr;
	int val;
	while (head != tail) {
		curr = queue[head++];
		if (head == len) {
			head = 0;
		}

		val = curr->val;
		int diff = k - val;
		int count = hashfind(root, table, diff);
		if (diff == val && count > 1) {
			for (h = 0; h < HASHSIZE; h++) {
				nfree(table[h]);
			}
			return true;
		} else if (diff != curr->val && count > 0) {
			for (int h = 0; h < HASHSIZE; h++) {
				nfree(table[h]);
			}
			return true;
		}
		hashfind(root, table, val);

		if (curr->left) {
			queue[tail++] = curr->left;
			if (tail == len) {
				tail = 0;
			}
			if (tail+1 == head) {
				int oldlen = len;
				len *= 2;
				struct TreeNode **oldqueue = queue;
				queue = (struct TreeNode **)calloc(len, sizeof(struct TreeNode *));
				if (head < tail) {
					for (i = 0, j = head; j < tail; i++, j++) {
						queue[i] = oldqueue[j];
					}
				} else {
					for (i = 0, j = head; j < oldlen; i++, j++) {
						queue[i] = oldqueue[j];
					}
					for (j = 0; j < tail; i++, j++) {
						queue[i] = oldqueue[j];
					}
				}
				head = 0;
				tail = i;
				free(oldqueue);
				oldqueue = NULL;
			}
		}
		if (curr->right) {
			queue[tail++] = curr->right;
			if (tail == len) {
				tail = 0;
			}
			if (tail+1 == head) {
				int oldlen = len;
				len *= 2;
				struct TreeNode **oldqueue = queue;
				queue = (struct TreeNode **)calloc(len, sizeof(struct TreeNode *));
				if (head < tail) {
					for (i = 0, j = head; j < tail; i++, j++) {
						queue[i] = oldqueue[j];
					}
				} else {
					for (i = 0, j = head; j < oldlen; i++, j++) {
						queue[i] = oldqueue[j];
					}
					for (j = 0; j < tail; i++, j++) {
						queue[i] = oldqueue[j];
					}
				}
				head = 0;
				tail = i;
				free(oldqueue);
				oldqueue = NULL;
			}
		}
	}
	for (h = 0; h < HASHSIZE; h++) {
		nfree(table[h]);
	}
	free(queue);
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


int
hashfind(struct TreeNode *root, struct HNode **table, int val)
{
	int h = hash(val);
	struct HNode *curr = table[h];
	while (curr) {
		if (curr->val == val) {
			return curr->count;
		}
		curr = curr->next;
	}
	int count = tsearch(root, val);
	struct HNode *new = (struct HNode *)malloc(sizeof(struct HNode));
	new->val = val;
	new->count = count;
	new->next = table[h];
	table[h] = new;
	return count;
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
nfree(struct HNode *head)
{
	if (head) {
		nfree(head->next);
		free(head);
	} else {
		return;
	}
}
