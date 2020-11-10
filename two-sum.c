#include <stdlib.h>

/**
 *  * Note: The returned array must be malloced, assume caller calls free().
 *   */
int* 
twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	*returnSize = 2;

	int i = 0;
	int j = 1;

	while (nums[i] + nums[j] != target) {
		if (++j == numsSize) {
			j = ++i + 1;
		}
	}
	int *a = (int *) malloc(2 * sizeof(int));
	a[0] = i;
	a[1] = j;
	return a;
}
