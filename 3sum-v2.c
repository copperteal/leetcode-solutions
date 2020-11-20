/* two-pointer on b,c
 * 164 ms
 * 31.23%
 * 79.93%
 */
#include <stdlib.h>

#define INITSIZE 16


void quicksort(int *nums, int left, int right);


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced,
 assume caller calls free().
 */
int**
threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
  if (numsSize < 3) {
    *returnSize = 0;
    *returnColumnSizes = NULL;
    return NULL;
  }

  int **out = (int **) malloc(INITSIZE * sizeof(int *));
  *returnColumnSizes = (int *) malloc(INITSIZE * sizeof(int));
  int rsize = 0;
  int rlen = INITSIZE;

  quicksort(nums, 0, numsSize-1);

  int i, j, k;
  int target, sum;
  for (i = 0; i < numsSize-2; i++) {
    /* deal with constant subarrays */
    while (0 < i && i < numsSize-2 && nums[i-1] == nums[i]) {
      i++;
    }
    target = -nums[i];
    for (j = i+1, k = numsSize-1; j < k; ) {
      sum = nums[j]+nums[k];
      if (sum > target) {
        k--;
        while (k >= 0 && nums[k] == nums[k+1]) {
          k--;
        }
      } else if (sum < target) {
        j++;
        while (j < numsSize && nums[j] == nums[j-1]) {
          j++;
        }
      } else {
        /* add to out */
        out[rsize] = (int *) malloc(3 * sizeof(int));
        out[rsize][0] = nums[i];
        out[rsize][1] = nums[j];
        out[rsize][2] = nums[k];
        (*returnColumnSizes)[rsize] = 3;
        rsize++;
        if (rsize == rlen) {
          rlen <<= 1;
          out = (int **) realloc(out, rlen * sizeof(int *));
          *returnColumnSizes = (int *) realloc(*returnColumnSizes, rlen * sizeof(int));
        }
        j++;
        while (j < numsSize && nums[j] == nums[j-1]) {
          j++;
        }
      }
    }
  }

  *returnSize = rsize;
  if (rsize) {
    out = realloc(out, rsize * sizeof(int *));
    *returnColumnSizes = realloc(*returnColumnSizes, rsize * sizeof(int));
    return out;
  } else {
    free(out);
    free(*returnColumnSizes);
    *returnColumnSizes = NULL;
    return NULL;
  }
}


int
partition(int *nums, int left, int right)
{
  int pivot = nums[right];
  int i, j, temp;
  for (i = left, j = left; j < right; j++) {
    if (nums[j] <= pivot) {
      temp = nums[i];
      nums[i] = nums[j];
      nums[j] = temp;
      i++;
    }
  }
  nums[right] = nums[i];
  nums[i] = pivot;
  return i;
}


void
quicksort(int *nums, int left, int right)
{
  if (left < right) {
    int mid = partition(nums, left, right);
    quicksort(nums, left, mid-1);
    quicksort(nums, mid+1, right);
  }
}
