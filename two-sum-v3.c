/* using a proper hash table */
#include <stdlib.h>

#define TABLESIZE 101

struct node {
	int val;
	int idx;
	struct node *next;
};

int hash(int);
int lookup(struct node**, int);
void insert(struct node**, int, int);
void freetable(struct node**);
void freelist(struct node*);

int*
twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	*returnSize = 2;

	struct node **table = (struct node**)calloc(TABLESIZE, sizeof(struct node*));
	int i, j;
	int diff;

	for (i = 0; i < numsSize; i++) {
		diff = target - nums[i];
		j = lookup(table, diff);
		if (j < 0) {
			insert(table, nums[i], i);
		} else {
			break;
		}
	}
	freetable(table);
	int *rv = (int*)malloc(*returnSize * sizeof(int));
	rv[0] = j;
	rv[1] = i;
	return rv;
}

int
hash(int val)
{
	val %= TABLESIZE;
	val *= 33;
	val %= TABLESIZE;
	val += (val < 0) ? TABLESIZE : 0;
	return val;
}

int
lookup(struct node **table, int val)
{
	int h = hash(val);
	struct node *head = table[h];
	while (head != NULL) {
		if (head->val == val) {
			return head->idx;
		}
		head = head->next;
	}
	return -1;
}

void
insert(struct node **table, int val, int idx)
{
	int h = hash(val);
	if (table[h] == NULL) {
		table[h] = (struct node*)malloc(sizeof(struct node));
		table[h]->val = val;
		table[h]->idx = idx;
		table[h]->next = NULL;
	} else {
		struct node *head = table[h];
		while (head->next != NULL) {
			head = head->next;
		}
		head->next = (struct node*)malloc(sizeof(struct node));
		head = head->next;
		head->val = val;
		head->idx = idx;
		head->next = NULL;
	}
}

void
freetable(struct node **table)
{
	for (int i = 0; i < TABLESIZE; i++) {
		freelist(table[i]);
	}
}

void
freelist(struct node *head)
{
	if (head == NULL) {
		return;
	} else if (head->next != NULL) {
		freelist(head->next);
	}
	free(head);
}
