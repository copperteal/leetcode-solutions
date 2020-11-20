/* dynamic programming
 * 4 ms
 * 21.64%
 * 13.43%
 */
#include <stdlib.h>


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced,
 assume caller calls free().
 */
int**
generate(int numRows, int* returnSize, int** returnColumnSizes)
{
  *returnSize = numRows;
  *returnColumnSizes = (int *) malloc(numRows * sizeof(int));
  int **pascal = (int **) malloc(numRows * sizeof(int *));
  int row, col;
  for (row = 0; row < numRows; row++) {
    (*returnColumnSizes)[row] = row+1;
    pascal[row] = (int *) malloc((row+1) * sizeof(int));
    pascal[row][0] = pascal[row][row] = 1;
    for (col = 1; col < row; col++) {
      pascal[row][col] = pascal[row-1][col-1] + pascal[row-1][col];
    }
  }
  return pascal;
}
