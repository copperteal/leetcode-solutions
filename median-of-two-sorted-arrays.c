/* Merge Sort
 * 8 ms
 * 97.67%
 * 50.44%
 */
#include <stdlib.h>


double
findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
	/* merge */
	int nums3Size = nums1Size + nums2Size;
	int *nums3 = (int *) malloc(nums3Size * sizeof(int));
	int i, j, k;
	for (i = j = k = 0; i < nums1Size && j < nums2Size; k++) {
		if (nums1[i] < nums2[j]) {
			nums3[k] = nums1[i++];
		} else {
			nums3[k] = nums2[j++];
		}
	}
	while (i < nums1Size) {
		nums3[k++] = nums1[i++];
	}
	while (j < nums2Size) {
		nums3[k++] = nums2[j++];
	}
	double med;
	if (nums3Size % 2) {
		/* odd */
		med = nums3[nums3Size / 2];
	} else {
		/* even */
		med = (nums3[nums3Size / 2] + nums3[(nums3Size / 2)-1]) * 0.5;
	}
	free(nums3);
	return med;
}
