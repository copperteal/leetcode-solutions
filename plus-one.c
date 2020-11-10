#include <stdlib.h>

/*
 * Note: The returned array must be malloced, assume caller calls free().
 */

/* Double pass */
int* plusOne(int* digits, int digitsSize, int* returnSize){
	int i;
	int carry = 1;
	for (i = digitsSize-1; i >= 0; i--) {
		digits[i] += carry;
		carry = digits[i] / 10;
		digits[i] %= 10;
	}

	int shift = 0;
	if (carry != 0)
		shift = 1;
	*returnSize = digitsSize + shift;
	int *array = (int*)malloc((*returnSize)*sizeof(int));
	array[0] = carry;
	for (i = 0; i < digitsSize; i++)
		array[i+shift] = digits[i];
	return array;
}
