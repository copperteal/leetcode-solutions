#define UP  1
#define DOWN 0

/* Zig-Zag algorithm: The max sum will start and finish on an uphill 
 * trajectory, if there is one. Otherwise, it will be the negative element
 * closest to zero.
 * */
int maxSubArray(int* nums, int numsSize){
	int i;
	int max, total, curr;
	int mode;
	if (nums[0] < 0) {
		mode = DOWN;
	} else {
		mode = UP;
	}

	max = nums[0];
	curr = total = 0;
	for (i = 0; i < numsSize; i++) {
		if (mode == UP) {
			if (nums[i] < 0) {
				mode = DOWN;
				total += curr;
				if (total < curr)
					total = curr;
				if (max < total)
					max = total;
				total += nums[i];
			} else {
				curr += nums[i];
			}
		} else {
			if (nums[i] < 0) {
				total += nums[i];
				if (nums[i] > max)
					max = nums[i];
			} else {
				mode = UP;
				curr = nums[i];
			}
		}
	}
	if (mode == UP) {
		total += curr;
		if (total < curr) {
			total = curr;
		}
		if (max < total) {
			max = total;
		}
	}

	return max;
}
