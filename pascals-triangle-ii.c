/* dynamic programming
 * 0ms
 * 100.00%
 * 55.81%
 */
#include <stdlib.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int*
getRow(int rowIndex, int* returnSize)
{
  if (rowIndex == 0) {
    *returnSize = 1;
    int *out = (int *) malloc(sizeof(int));
    out[0] = 1;
    return out;
  }

  *returnSize = rowIndex+1;
  int *prevRow = (int *) malloc((rowIndex+1) * sizeof(int));
  prevRow[0] = 1;
  int *nextRow = (int *) malloc((rowIndex+1) * sizeof(int));
  nextRow[0] = 1;
  int row, col;
  for (row = 1; row < rowIndex+1; row++) {
    prevRow[row] = 1;
    nextRow[row] = 1;
    for (col = 1; col < row; col++) {
      nextRow[col] = prevRow[col-1] + prevRow[col];
      prevRow[col-1] = nextRow[col-1];
    }
    prevRow[row-1] = nextRow[row-1];
  }
  free(prevRow);
  return nextRow;
}
