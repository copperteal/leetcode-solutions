/* hash table with counts, then "n choose 2"
 * 48 ms
 * 50.00%
 * 50.00%
 */
#include <stdlib.h>
#define TABLESIZE 101

struct table_node {
  int first;
  int second;
  int count;
  struct table_node *next;
};
typedef struct table_node *NodePtr;
void insert(NodePtr *table, int first, int second);
int count_free(NodePtr head);

int
numEquivDominoPairs(int** dominoes, int dominoesSize, int* dominoesColSize)
{
  /* fill table */
  NodePtr *table = (NodePtr *) calloc(TABLESIZE, sizeof(NodePtr));
  int i, a, b;
  for (i = 0; i < dominoesSize; i++) {
    a = dominoes[i][0];
    b = dominoes[i][1];
    if (a < b) {
      insert(table, a, b);
    } else {
      insert(table, b, a);
    }
  }
  /* get count and free table */
  int count = 0;
  for (i = 0; i < TABLESIZE; i++) {
    if (table[i]) {
      count += count_free(table[i]);
    }
  }
  free(table);
  return count;
}


/* assume that first does not exceed second */
int
hash(int first, int second)
{
  return ((first * 33 + second) * 33 + 17) % TABLESIZE;
}


void
insert(NodePtr *table, int first, int second)
{
  int h = hash(first, second);
  NodePtr curr;
  for (curr = table[h];
       curr && (curr->first != first || curr->second != second);
       curr = curr->next)
    ;
  if (curr) {
    (curr->count)++;
  } else {
    curr = (NodePtr) malloc(sizeof(struct table_node));
    curr->first = first;
    curr->second = second;
    curr->count = 1;
    curr->next = table[h];
    table[h] = curr;
  }
}


int
count_free(NodePtr head)
{
  int count = head->count;
  count = count * (count-1) / 2;  /* "n choose 2" */
  if (head->next) {
    count += count_free(head->next);
  }
  free(head);
  return count;
}
