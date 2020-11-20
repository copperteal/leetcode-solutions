/* straight forward
 * 44 ms
 * 48.15%
 * 11.11%
 */
#include <stdlib.h>


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced,
 assume caller calls free().
 */
int**
matrixReshape(int** nums, int numsSize, int* numsColSize, int r, int c, int* returnSize, int** returnColumnSizes)
{
  /* check legality */
  if (numsSize * (*numsColSize) != r * c) {
    *returnSize = numsSize;
    *returnColumnSizes = (int *) malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
      (*returnColumnSizes)[i] = *numsColSize;
    }
    return nums;
  }

  int i, j, p, q;
  /* initialize empty array */
  int **out = (int **) malloc(r * sizeof(int *));
  out[0] = (int *) malloc(c * sizeof(int));
  *returnSize = r;
  *returnColumnSizes = (int *) malloc(r * sizeof(int));
  p = q = 0;
  for (i = 0; i < numsSize; i++) {
    for (j = 0; j < *numsColSize; j++) {
      out[p][q++] = nums[i][j];
      if (q == c) {
        (*returnColumnSizes)[p] = c;
        q = 0;
        p++;
        if (p != r) {
          out[p] = (int *) malloc(c * sizeof(int));
        }
      }
    }
  }
  return out;
}
