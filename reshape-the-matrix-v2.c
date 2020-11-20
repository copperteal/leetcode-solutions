/* modular (Euclidean Algorithm)
 * convert to absolute index, then find quotient and remainder
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

  int i, j, idx, p, q;
  /* initialize empty array */
  int **out = (int **) malloc(r * sizeof(int *));
  *returnSize = r;
  *returnColumnSizes = (int *) malloc(r * sizeof(int));
  for (p = 0; p < r; p++) {
    out[p] = (int *) malloc(c * sizeof(int));
    (*returnColumnSizes)[p] = c;
  }
  for (i = 0; i < numsSize; i++) {
    for (j = 0; j < *numsColSize; j++) {
      idx = i * (*numsColSize) + j;
      q = idx % c;
      p = (idx - q) / c;
      out[p][q] = nums[i][j];
    }
  }
  return out;
}
