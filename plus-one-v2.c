#include <stdlib.h>

/*
 * Note: The returned array must be malloced, assume caller calls free().
 */

/* Pre-emptive check for carry. Single pass. */
int* plusOne(int* digits, int digitsSize, int* returnSize){
	int i;

	for (i = 0; i < digitsSize && digits[i] == 9; i++)
		;
	int shift = (i != digitsSize) ? 0 : 1;
	*returnSize = digitsSize + shift;
	int *array = (int*)malloc((*returnSize)*sizeof(int));
	if (shift != 0)
		array[0] = 1;

	int carry = 1;
	for (i = digitsSize-1; i >= 0; i--) {
		if (carry != 0) {
			digits[i] += 1;
			carry = (digits[i] > 9);
			array[i+shift] = digits[i] % 10;
		} else {
			array[i+shift] = digits[i];
		}
	}
	return array;
}
