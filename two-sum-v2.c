#include <stdlib.h>

int match(int hash[], int max, int val) {
	int i;
	for (i = 0; i < max; i += 2) {
		if (hash[i] == val)
			return i+1;
	}
	return 0;
}

/* using a lookup table */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
	*returnSize = 2;

	int i, j, k, diff;
	int hash_size = 2 * numsSize;
	int hash[hash_size];
	
	for (i = 0; i < numsSize; i++) {
		diff = target - nums[i];
		j = 2 * i;
		k = match(hash, j, diff);
		if (k)
			break;
		hash[j] = nums[i];
		hash[j+1] = i;
	}
	int *a = (int *) malloc(2 * sizeof(int));
	a[0] = hash[k];
	a[1] = i;
	return a;
}
