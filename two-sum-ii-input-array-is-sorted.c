#include <stdlib.h>


int*
twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
	*returnSize = 2;
	if (numbersSize < 3) {
		int *rv = (int*)malloc(2*sizeof(int));
		rv[0] = 1;
		rv[1] = 2;
	}

	int lidx, ridx;
	for (lidx = 0, ridx = numbersSize-1; lidx < ridx; ) {
		if (target - numbers[lidx] < numbers[ridx]) {
			ridx--;
		} else if  (target - numbers[lidx] > numbers[ridx]) {
			lidx++;
		} else {
			break;
		}
	}
	int *rv = (int*)malloc(2*sizeof(int));
	rv[0] = ++lidx;
	rv[1] = ++ridx;
	return rv;
}
