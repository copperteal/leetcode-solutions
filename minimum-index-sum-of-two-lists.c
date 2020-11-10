/* 52 ms
 * 70.00%
 * 10.00%
 */
#include <stdlib.h>
#include <string.h>

#define TSIZE 101
#define LINIT 8


/*
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct node_t {
int index;
char *name;
struct node_t *next;
};
int hash(char *name);
void insert(struct node_t **table, int index, char *name);
int lookup(struct node_t **table, char *name);
void nfree(struct node_t *head);


char **
findRestaurant(char ** list1, int list1Size, char ** list2, int list2Size, int* returnSize)
{
	struct node_t **table = (struct node_t **) calloc(TSIZE, sizeof(struct node_t *));
	int i, j;
	for (i = 0; i < list1Size; i++) {
		insert(table, i, list1[i]);
	}

	int min = -1;
	int lmax = LINIT;
	int count = 0;
	char **list3 = (char **) calloc(lmax, sizeof(char *));
	for (i = 0; i < list2Size; i++) {
		j = lookup(table, list2[i]);
		if (j < 0) {
			continue;
		}
		if (min < 0 || i+j < min) {
			min = i+j;
			list3[0] = list2[i];
			count = 1;
		} else if (i+j == min) {
			if (count == lmax) {
				lmax <<= 1;
				list3 = reallocarray(list3, lmax, sizeof(char *));
			}
			list3[count++] = list2[i];
		}
	}

	for (i = 0; i < TSIZE; i++) {
		nfree(table[i]);
	}
	*returnSize = count;
	return list3;
}


int
hash(char *name)
{
	int h = 0;
	while (*name != '\0') {
		h = ((h << 5) + h + *(name++)) % TSIZE;
	}
	return h;
}


void
insert(struct node_t **table, int index, char *name)
{
	int h = hash(name);
	struct node_t *curr;
	for (curr = table[h]; curr; curr = curr->next) {
		if (strcmp(curr->name, name) != 0) {
			continue;
		} else {
			return;
		}
	}
	curr = (struct node_t *) malloc(sizeof(struct node_t));
	curr->index = index;
	curr->name = name;
	curr->next = table[h];
	table[h] = curr;
}


int
lookup(struct node_t **table, char *name)
{
	int h = hash(name);
	struct node_t *curr;
	for (curr = table[h]; curr; curr = curr->next) {
		if (strcmp(curr->name, name) != 0) {
			continue;
		} else {
			return curr->index;
		}
	}
	return -1;
}


void
nfree(struct node_t *head)
{
	if (head) {
		nfree(head->next);
		free(head);
	}
}
