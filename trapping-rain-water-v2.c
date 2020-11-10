/* 4 ms
 * 86.30%
 * 37.44%
 */
#define max(A,B) ((A) > (B) ? (A) : (B))
#define min(A,B) ((A) < (B) ? (A) : (B))


/* O(3n) solution */
int
trap(int* height, int heightSize)
{
	if (heightSize < 3) {
		return 0;
	}

	int i;
	int count = 0;
	int leftmax[heightSize];
	leftmax[0] = height[0];
	for (i = 1; i < heightSize; i++) {
		leftmax[i] = max(leftmax[i-1], height[i]);
	}

	int rightmax[heightSize];
	rightmax[heightSize-1] = height[heightSize-1];
	for (i = heightSize-2; i >= 0; i--) {
		rightmax[i] = max(rightmax[i+1], height[i]);
	}

	for (i = 0; i < heightSize; i++) {
		count += max(0, min(leftmax[i], rightmax[i]) - height[i]);
	}
	return count;
}
