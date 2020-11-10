/* 100% */
#include <stdlib.h>
#define TABLESIZE 1000

struct node {
	int key;
	int freq;
	struct node *next;
};

typedef struct {
	struct node **table;
} TwoSum;

int hash(int);
int lookup(struct node**, int);
void freeList(struct node*);

/** Initialize your data structure here. */

TwoSum*
twoSumCreate()
{
	TwoSum *new = (TwoSum*)malloc(sizeof(TwoSum));
	new->table = (struct node**)calloc(TABLESIZE, sizeof(struct node*));
	return new;
}

/** Add the number to an internal data structure.. */
void
twoSumAdd(TwoSum* obj, int number)
{
	int h = hash(number);
	struct node *curr = (obj->table)[h];
	if (curr == NULL) {
		curr = (struct node*)malloc(sizeof(struct node));
		curr->key = number;
		curr->freq = 1;
		curr->next = NULL;
		(obj->table)[h] = curr;
		return;
	}
	while (curr->next != NULL) {
		if (curr->key == number) {
			(curr->freq)++;
			return;
		} else {
			curr = curr->next;
		}
	}
	if (curr->key == number) {
		(curr->freq)++;
		return;
	}
	curr->next = (struct node*)malloc(sizeof(struct node));
	curr = curr->next;
	curr->key = number;
	curr->freq = 1;
	curr->next = NULL;
}

/** Find if there exists any pair of numbers which sum is equal to the value.
 */
bool
twoSumFind(TwoSum* obj, int value)
{
	if (value > 100000 || value < -100000) {
		return false;
	}

	struct node **table = obj->table;
	struct node *curr;
	int h;
	int diff;
	int freq;
	for (h = 0; h < TABLESIZE; h++) {
		if (table[h] != NULL) {
			curr = table[h];
			while (curr != NULL) {
				diff = value - curr->key;
				freq = lookup(table, diff);
				if (curr->key == diff && freq > 1) {
					return true;
				} else if (curr->key != diff && freq > 0) {
					return true;
				} else {
				curr = curr->next;
				}
			}
		}
	}
	return false;
}

void
twoSumFree(TwoSum* obj)
{
	for (int h = 0; h < TABLESIZE; h++) {
		freeList((obj->table)[h]);
	}
	free(obj->table);
	obj->table = NULL;
	free(obj);
}

/**
 * Your TwoSum struct will be instantiated and called as such:
 * TwoSum* obj = twoSumCreate();
 * twoSumAdd(obj, number);
 
 * bool param_2 = twoSumFind(obj, value);
 
 * twoSumFree(obj);
 */

int
hash(int n)
{
	n %= TABLESIZE;
	n *= 33;
	n %= TABLESIZE;
	return (n < 0) ? TABLESIZE + n : n;
}

int
lookup(struct node **table, int key)
{
	int h = hash(key);
	struct node *curr = table[h];
	while (curr != NULL) {
		if (curr->key == key) {
			return curr->freq;
		}
		curr = curr->next;
	}
	return 0;
}

void
freeList(struct node *head)
{
	if (head == NULL) {
		return;
	} else if (head->next != NULL) {
		freeList(head->next);
	}
	free(head);
}
