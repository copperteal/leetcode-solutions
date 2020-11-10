/* 40.00%
 * 6.67%
 */
#include <stdbool.h>
#include <stdlib.h>

#define HASHSIZE 199  /* prime close to 200 */

typedef struct node node_t;

struct node {
	int val;
	struct node *next;
};

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};


node_t * nalloc(int, node_t *);
void nfree(node_t *);
void tfree(node_t **);
int hash(int);
bool search(node_t **, struct TreeNode *, int);


/* hash table version */
bool
findTarget(struct TreeNode *root, int k)
{
	node_t **table = (node_t **)calloc(HASHSIZE, sizeof(node_t*));
	bool val = search(table, root, k);
	tfree(table);
	return val;
}

node_t *
nalloc(int val, node_t *next)
{
	node_t *new = (node_t *)malloc(sizeof(node_t));
	new->val = val;
	new->next = next;
	return new;
}

void
nfree(node_t *head)
{
	if (head) {
		nfree(head->next);
		free(head);
	} else {
		return;
	}
}

void
tfree(node_t **table)
{
	for (int h = 0; h < HASHSIZE; h++) {
		nfree(table[h]);
	}
	free(table);
}

bool
search(node_t **table, struct TreeNode *root, int k)
{
	if (root->left && search(table, root->left, k)) {
		return true;
	} else if (root->right && search(table, root->right, k)) {
		return true;
	}
	int diff = k - root->val;
	int h = hash(diff);
	node_t *curr;
	if (table[h]) {
		curr = table[h];
		while (curr) {
			if (curr->val == diff) {
				return true;
			}
			curr = curr->next;
		}
	}
	h = hash(root->val);
	curr = nalloc(root->val, table[h]);
	table[h] = curr;
	return false;
}


int
hash(int n)
{
	n %= HASHSIZE;
	n *= 33;
	n %=HASHSIZE;
	return (n < 0) ? n + HASHSIZE : n;
}
