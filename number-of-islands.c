/* DFS
 * 8 ms
 * 98.61%
 * 5.09%
 */
#include <stdlib.h>

void push(int *stack, int i, int j);
void pop(int *stack, int *i, int *j);

int
numIslands(char** grid, int gridSize, int* gridColSize)
{
	int numCols = gridColSize[0];
	int numRows = gridSize;
	int row, col, i, j;
	/* stack[0] == size + 1 */
	int *stack = (int *) malloc((numRows * numCols * 2 + 1) * sizeof(int));
	stack[0] = 1;
	int count = 0;
	i = j = 0;
	for (row = 0; row < numRows; row++) {
		for (col = 0; col < numCols; col++) {
			if (grid[row][col] == '1') {
				/* initiate DFS */
				push(stack, row, col);
				while (stack[0] > 1) {
					pop(stack, &i, &j);
					grid[i][j] = '0';
					/* North */
					if (i > 0 && grid[i-1][j] == '1') {
						push(stack, i-1, j);
					}
					/* East */
					if (j < numCols-1 && grid[i][j+1] == '1') {
						push(stack, i, j+1);
					}
					/* South */
					if (i < numRows-1 && grid[i+1][j] == '1') {
						push(stack, i+1, j);
					}
					/* West */
					if (j > 0 && grid[i][j-1] == '1') {
						push(stack, i, j-1);
					}
				}
				count++;
			}
		}
	}
	free(stack);
	return count;
}

void
push(int *stack, int i, int j)
{
	int top = stack[0];
	stack[0] += 2;
	stack[top] = i;
	stack[top+1] = j;
}

void
pop(int *stack, int *i, int *j)
{
	stack[0] -= 2;
	int top = stack[0];
	 i = stack[top];
	 j = stack[top+1];
}
