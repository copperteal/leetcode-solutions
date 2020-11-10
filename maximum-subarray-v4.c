

/* Kadane's algorithm */
int maxSubArray(int* nums, int numsSize){
	int i;
	int curr = 0;
	for (i = 0; i < numsSize; i++) {
		if (curr < 0) {
			curr = nums[i];
		} else {
			curr += nums[i];
			nums[i] = curr;
		}
	}
	int max = nums[0];
	for (i = 0; i < numsSize; i++) {
		if (max < nums[i])
			max = nums[i];
	}
	return max;
}
