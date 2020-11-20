/* binary search for c
 * 272 ms
 * 21.56%
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

  int i, j;
  int a, b, c;
  int left, right, mid;
  for (i = 0; i < numsSize-2; i++) {
    /* deal with constant subarrays */
    while (0 < i && i < numsSize-2 && nums[i-1] == nums[i]) {
      i++;
    }
    a = nums[i];
    for (j = i+1; j < numsSize-1; j++) {
      b = nums[j];
      c = -(a+b);
      /* binary search for c */
      left = j+1;
      right = numsSize-1;
      while (left <= right) {
        mid = (left+right)/2;
        if (c < nums[mid]) {
          right = mid-1;
        } else if (c > nums[mid]) {
          left = mid+1;
        } else {
          /* found candidate */
          if (rsize == 0 || out[rsize-1][0] != a ||
          out[rsize-1][1] != b || out[rsize-1][2] != c ) {
            /* add to out */
            out[rsize] = (int *) malloc(3 * sizeof(int));
            out[rsize][0] = a;
            out[rsize][1] = b;
            out[rsize][2] = c;
            (*returnColumnSizes)[rsize] = 3;
            rsize++;
            if (rsize == rlen) {
              rlen <<= 1;
              out = (int **) realloc(out, rlen * sizeof(int *));
              *returnColumnSizes = (int *) realloc(*returnColumnSizes, rlen * sizeof(int));
            }
          }
          break;
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
