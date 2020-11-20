/* two index tables
 * 20 ms
 * 96.00%
 * 16.00%
 */
#include <stdlib.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *
luckyNumbers(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
  int i, j;
  /* find min index of each row */
  /* and max index of each col */
  int min[matrixSize];
  for (i = 0; i < matrixSize; i++) {
    min[i] = 0;
  }
  int max[*matrixColSize];
  for (j = 0; j < *matrixColSize; j++) {
    max[j] = 0;
  }
  for (i = 0; i < matrixSize; i++) {
    for (j = 0; j < *matrixColSize; j++) {
      if (matrix[i][min[i]] > matrix[i][j]) {
        min[i] = j;
      }
      if (matrix[max[j]][j] < matrix[i][j]) {
        max[j] = i;
      }
    }
  }
  /* list lucky numbers */
  int count = 0;
  int *lucky = (int *) malloc(matrixSize * sizeof(int));
  for (i = 0; i < matrixSize; i++) {
    if (i == max[min[i]]) {
      lucky[count++] = matrix[i][min[i]];
    }
  }
  *returnSize = count;
  return lucky;
}
