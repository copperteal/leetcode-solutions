

/* start at end! */
void
merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
	int i, j, k;
	for (i = m-1, j = n-1, k = m+n-1; i >= 0 && j >= 0 && k >= 0; k--) {
		if (nums1[i] > nums2[j]) {
			nums1[k] = nums1[i--];
		} else {
			nums1[k] = nums2[j--];
		}
	}
	if (i < 0) {
		while (j >= 0) {
			nums1[k--] = nums2[j--];
		}
	}
}
