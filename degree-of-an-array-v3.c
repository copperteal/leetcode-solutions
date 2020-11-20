/* count first
 * 100 ms
 * 15.38%
 * 17.95%
 */
#include <stdlib.h>

int
findShortestSubArray(int* nums, int numsSize)
{
  int mdigit = 0;
  int i, j, k;
  /* find max val in nums */
  for (i = 0; i < numsSize; i++) {
    if (nums[i] > mdigit) {
      mdigit = nums[i];
    }
  }
  int *counts = (int *) calloc(mdigit+1, sizeof(int));
  int maxfreq = 0;
  /* count number of occurrences of each val in nums,
   * keeping track of max frequency
   */
  for (i = 0; i < numsSize; i++) {
    counts[nums[i]]++;
    if (counts[nums[i]] > maxfreq) {
      maxfreq = counts[nums[i]];
    }
  }
  int minlen = numsSize;
  /* calculate minimum length */
  for (i = 0; i <= mdigit; i++) {
    if (counts[i] == maxfreq) {
      for (j = 0; nums[j] != i; j++)
        ;
      for (k = numsSize-1; nums[k] != i; k--)
        ;
      if (minlen+j > k+1) {
        minlen = k-j+1;
      }
    }
  }
  return minlen;
}
