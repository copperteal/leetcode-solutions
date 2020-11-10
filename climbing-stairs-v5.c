#include <stdlib.h>


int f[2][2] = {
	{1, 1},
	{1, 0}
};


int **iter(int **a);


/* Binet's method: Fibonacci Numbers with matrix iteriplication */
int climbStairs(int n){
	if (n < 3) {
		return n;
	}

	int **a = (int**)calloc(2, sizeof(int*));
	int i, j;
	for (i = 0; i < 2; i++) {
		a[i] = (int*)calloc(2, sizeof(int));
	}
	a[0][0] = 1;
	a[1][1] = 1;

	for (i = 0; i < n; i++) {
		a = iter(a);
	}
	int out = a[0][0];
	free(a);
	return out;
}


int **iter(int **a) {
	int **c = (int**)calloc(2, sizeof(int*));
		int i, j, k;
		for (i = 0; i < 2; i++)
		c[i] = (int*)calloc(2, sizeof(int));
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			for (k = 0; k < 2; k++)
				c[i][j] += a[i][k] * f[k][j];
		}
	}
	free(a);
	return c;
}
