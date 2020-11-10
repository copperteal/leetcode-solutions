
int removeDuplicates(int* nums, int numsSize){
	if (numsSize < 2) {
		return numsSize;
	}

	int i, j, curr;

	j = 0;
	curr = nums[0];
	for (i = 1; i < numsSize; i++) {
		if (nums[i] != curr) {
			j++;
			curr = nums[i];
			nums[i] = nums[j];
			nums[j] = curr;
		}
	}
	return ++j;
}
