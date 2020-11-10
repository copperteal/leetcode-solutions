

/* Divide and Conquer */
int midSum(int* nums, int numsSize, int midPoint);

int maxSubArray(int* nums, int numsSize)
{
	if (numsSize == 1) {
		return nums[0];
	}

	int midPoint = numsSize / 2;
	int left = maxSubArray(nums, midPoint);
	int right = maxSubArray(nums+midPoint, numsSize - midPoint);
	int mid = midSum(nums, numsSize, midPoint);

	if (left >= right && left >= mid) {
		return left;
	} else if (right >= left && right >= mid) {
		return right;
	}
	return mid;
}

int
midSum(int* nums, int numsSize, int midPoint)
{
	if (numsSize == 2) {
		return (nums[0] > 0) ? nums[0] + nums[1] : nums[1];
	}

	int lsum = nums[midPoint];
	int lmax = lsum;
	int rsum = nums[midPoint+1];
	int rmax;
	if (rsum < 0) {
		rmax = 0;
	} else {
		rmax = rsum;
	}
	int i;
	for (i = midPoint-1; i >= 0; i--) {
		lsum += nums[i];
		if (lmax < lsum)
			lmax = lsum;
	}
	for (i = midPoint+2; i < numsSize; i++) {
		rsum += nums[i];
		if (rmax < rsum)
			rmax = rsum;
	}
	return lmax + rmax;
}
