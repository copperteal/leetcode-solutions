#include <stdlib.h>


void
merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
	int i, j, k;

	if (m == 0) {
		for (j = 0; j < n; j++) {
			nums1[j] = nums2[j];
		}
		return;
	} else if (n == 0) {
		return;
	}

	int *nums3 = (int*)calloc(m, sizeof(int));
	for (k = 0; k < m; k++) {
		nums3[k] = nums1[k];
	}
	j = k = 0;
	for (i = 0; i < m+n && j < n && k < m; i++) {
		if (nums2[j] < nums3[k]) {
			nums1[i] = nums2[j++];
		} else {
			nums1[i] = nums3[k++];
		}
	}
	if (i == m+n) {
		free(nums3);
		return;
	} else if (j == n) {
		for ( ; k < m; k++) {
			nums1[i++] = nums3[k];
		}
	} else if (k == m) {
		for ( ; j < n; j++) {
			nums1[i++] = nums2[j];
		}
	}
	free(nums3);
}
