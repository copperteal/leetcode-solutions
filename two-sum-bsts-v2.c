/* 24ms
* 25.00%
* 75.00%
*/
#include <stdbool.h>
#include <stdlib.h>
#define TSIZE 101

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct tablenode {
	int val;
	struct tablenode *next;
};
typedef struct tablenode tnode;
int hash(int);
void insert(tnode **, int);
bool lookup(tnode **, int);
void filltable(tnode **table, struct TreeNode *root, int);
bool findmatch(tnode **, struct TreeNode *root);
void tfree(tnode **);
void lfree(tnode *);

bool
twoSumBSTs(struct TreeNode* root1, struct TreeNode* root2, int target)
{
	tnode **table = (tnode **) calloc(TSIZE, sizeof(tnode *));
	filltable(table, root1, target);
	bool ans = findmatch(table, root2);
	tfree(table);
	return ans;
}


int
hash(int val)
{
	val %= TSIZE;
	val *= 33;
	val %= TSIZE;
	return (val < 0) ? val+TSIZE : val;
}


void
insert(tnode **table, int val)
{
	int h = hash(val);
	tnode *new = (tnode *) malloc(sizeof(tnode));
	new->val = val;
	new->next = table[h];
	table[h] = new;
}


bool
lookup(tnode **table, int val)
{
	int h = hash(val);
	tnode *curr;
	for (curr = table[h]; curr; curr = curr->next) {
		if (curr->val == val) {
			return true;
		}
	}
	return false;
}


void
filltable(tnode **table, struct TreeNode *root, int target)
{
	if (root == NULL) {
		return;
	}
	filltable(table, root->left, target);
	insert(table, target - root->val);
	filltable(table, root->right, target);
}


bool
findmatch(tnode **table, struct TreeNode *root)
{
	if (root == NULL) {
		return false;
	}
	return lookup(table, root->val)
	|| findmatch(table, root->left)
	|| findmatch(table, root->right);
}


void
tfree(tnode **table)
{
	int h;
	for (h = 0; h < TSIZE; h++) {
		lfree(table[h]);
	}
	free(table);
}

void
lfree(tnode *node)
{
	if (node) {
		lfree(node->next);
		free(node);
	}
}
