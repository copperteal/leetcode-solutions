/* hash table
 * 100 ms
 * 15.38%
 * 15.38%
 */
#include <stdlib.h>
#define TABLESIZE 101

struct table_node {
  int val;
  int freq;
  int len;
  struct table_node *next;
};
typedef struct table_node *TabPtr;
/* want to access both freq and len by val */
TabPtr lookup(int *nums, int size, TabPtr *table, int val);
void freeList(TabPtr head);


int
findShortestSubArray(int* nums, int numsSize)
{
  int i;

  TabPtr table[TABLESIZE];
  for (i = 0; i < TABLESIZE; i++) {
    table[i] = NULL;
  }

  TabPtr curr;
  int maxfreq = 1;
  for (i = 0; i < numsSize; i++) {
    curr = lookup(nums, numsSize, table, nums[i]);
    if (curr->freq > maxfreq) {
      maxfreq = curr->freq;
    }
  }

  int minlen = numsSize;
  for (i = 0; i < TABLESIZE; i++) {
    if (table[i]) {
      for (curr = table[i]; curr; curr = curr->next) {
        if (curr->freq == maxfreq && curr->len < minlen) {
          minlen = curr->len;
        }
      }
      freeList(table[i]);
    }
  }
  return minlen;
}


int
hash(int val)
{
  val %= TABLESIZE;
  val *= 33;
  val %= TABLESIZE;
  return (val < 0) ? val+TABLESIZE : val;
}


TabPtr
lookup(int *nums, int size, TabPtr *table, int val)
{
  int h = hash(val);
  TabPtr curr;
  for (curr = table[h]; curr && curr->val != val; curr = curr->next)
    ;
  if (curr) {
    /* val is already in the table */
    (curr->freq)++;
  } else {
    /* val is not in the table, yet */
    curr = (TabPtr) malloc(sizeof(struct table_node));
    curr->val = val;
    curr->freq = 1;
    /* calculate
     curr->len
     */
    int i, j;
    for (i = 0; nums[i] != val; i++)
      ;
    for (j = size-1; nums[j] != val; j--)
      ;
    curr->len = j-i+1;
    curr->next = table[h];
    table[h] = curr;
  }
  return curr;
}


void
freeList(TabPtr head)
{
  if (head) {
    if (head->next) {
      freeList(head->next);
    }
    free(head);
  }
}
