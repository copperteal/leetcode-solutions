

int searchInsert(int* nums, int numsSize, int target){
	int i;
	for (i = 0; i < numsSize && target > nums[i]; i++)
		;
	return i;
}
