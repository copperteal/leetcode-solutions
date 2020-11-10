/* too slow, table gets too big */
#include <stdlib.h>

#define INITSIZE 32
#define TABLESIZE 101


struct Node {
	int val;
	struct Node *next;
};

typedef struct {
	int *vals;
	int count;
	int size;
	struct Node **table; /* keeps track of sums */
} TwoSum;

int hash(int);
void freeList(struct Node*);
void freeTable(struct Node**);
void insertTable(struct Node **table, int val);
void updateTable(TwoSum*, int);

/** Initialize your data structure here. */

TwoSum*
twoSumCreate()
{
	TwoSum *new = (TwoSum*)malloc(sizeof(TwoSum));
	new->vals = (int*)malloc(INITSIZE * sizeof(int));
	new->count = 0;
	new->size = INITSIZE;
	new->table = (struct Node**)calloc(TABLESIZE, sizeof(struct Node*));
	return new;
}

/** Add the number to an internal data structure.. */
void
twoSumAdd(TwoSum* obj, int number)
{
	/* resize, if needed */
	if (obj->count == obj->size) {
		(obj->size) <<= 1;
		obj->vals = realloc(obj->vals, (obj->size) * sizeof(int));
	}
	int count = obj->count;
	updateTable(obj, number);
	(obj->vals)[obj->count] = number;
	(obj->count)++;
}

/** Find if there exists any pair of numbers which sum is equal to the value.
* * */
bool
twoSumFind(TwoSum* obj, int value)
{
	struct Node **table = obj->table;
	int h = hash(value);
	struct Node *curr = table[h];
	if (curr == NULL) {
		return false;
	}
	while (curr != NULL) {
		if (curr->val == value) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

void
twoSumFree(TwoSum* obj)
{
	free(obj->vals);
	obj->vals = NULL;
	freeTable(obj->table);
	obj->table = NULL;
	free(obj);
}

/**
* *  * Your TwoSum struct will be instantiated and called as such:
* *   * TwoSum* obj = twoSumCreate();
* *    * twoSumAdd(obj, number);
* *     
* *      * bool param_2 = twoSumFind(obj, value);
* *       
* *        * twoSumFree(obj);
* *        */

int
hash(int val)
{
	val %= TABLESIZE;
	val *= 33;
	val %= TABLESIZE;
	return (val < 0) ? val+TABLESIZE : val;
}

void
freeTable(struct Node **table)
{
	for (int h = 0; h < TABLESIZE; h++) {
		freeList(table[h]);
	}
	free(table);
}

void
freeList(struct Node *head)
{
	if (head == NULL) {
		return;
	} else if (head->next != NULL) {
		freeList(head->next);
	}
	free(head);
}

void
updateTable(TwoSum *obj, int val)
{
	struct Node **table = obj->table;
	int *vals = obj->vals;
	int count = obj->count;
	int i;
	for (i = 0; i < count; i++) {
		insertTable(table, val + vals[i]);
	}
}

void
insertTable(struct Node **table, int val)
{
	int h = hash(val);
	struct Node *head = table[h];
	if (head == NULL) {
		table[h] = (struct Node*)malloc(sizeof(struct Node));
		table[h]->val = val;
		table[h]->next = NULL;
		return;
	}
	while (head->next != NULL) {
		if (head->val == val) {
			return;
		} else {
			head = head->next;
		}
	}
	head->next = (struct Node*)malloc(sizeof(struct Node));
	head = head->next;
	head->val = val;
	head->next = NULL;
}
