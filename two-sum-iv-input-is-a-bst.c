/* 8.89% 
 * 6.67%
 */
#include <stdbool.h>
#include <stdlib.h>


#define INITSIZE 32


typedef struct {
	int *elem;
	int size;
	int max;
} list_t;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};


list_t *lcat(list_t *, list_t *);
void lfree(list_t *);
list_t *lalloc(int max);
list_t *ttol(struct TreeNode *);
bool twoptr(list_t *, int);


/* convert to array, then two-pointer */
bool
findTarget(struct TreeNode* root, int k)
{
	list_t *list = ttol(root);
	bool val =  twoptr(list, k);
	lfree(list);
	return val;
}


list_t *
lcat(list_t *l1, list_t *l2)
{
	list_t *l3 = lalloc(l1->max + l2->max);
	int i, j;
	for (i = 0; i < l1->size; i++) {
		l3->elem[i] = l1->elem[i];
	}
	for (i = 0, j = l1->size; i < l2->size; i++, j++) {
		l3->elem[j] = l2->elem[i];
	}
	l3->size = l1->size + l2->size;
	lfree(l1);
	lfree(l2);
	return l3;
}


void
lfree(list_t *list)
{
	free(list->elem);
	free(list);
}


list_t *
lalloc(int max)
{
	list_t *list = (list_t *)malloc(sizeof(list_t));
	list->elem = (int*)calloc(max, sizeof(int));
	list->size = 0;
	list->max = max;
	return list;
}

list_t *
ttol(struct TreeNode *root)
{
	if (root == NULL) {
		return NULL;
	}
	list_t *out = lalloc(1);
	out->elem[0] = root->val;
	out->size = 1;
	list_t *ll = ttol(root->left);
	if (ll != NULL) {
		out = lcat(ll, out);
	}
	list_t *rl = ttol(root->right);
	if (rl != NULL) {
		out = lcat(out, rl);
	}
	return out;
}

bool
twoptr(list_t *list, int k)
{
	int left, right;
	int *arr = list->elem;
	for (left = 0, right = list->size-1; left < right; ) {
		if (arr[left]+arr[right] > k) {
			right--;
		} else if (arr[left]+arr[right] < k) {
			left++;
		} else {
			return true;
		}
	}
	return false;
}
