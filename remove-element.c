

int removeElement(int* nums, int numsSize, int val){
	if (numsSize == 0) {
		return 0;
	}

	int i, j;

	for (i = 0, j = numsSize-1; i < j;) {
		if (nums[j] == val) {
			j--;
		} else if (nums[i] == val) {
			nums[i] = nums[j];
			nums[j] = val;
			i++;
		} else {
			i++;
		}
	}
	if (nums[j] == val)
		return j;
	else
		return j+1;
}
