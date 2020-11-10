/* 8 ms
 * 18.26%
 * 37.44%
 */
#define max(A,B) ((A) > (B) ? (A) : (B))
#define min(A,B) ((A) < (B) ? (A) : (B))


/* O(n^2) solution */
int
trap(int* height, int heightSize)
{
	if (heightSize < 3) {
		return 0;
	}

	int lstart = 0;
	int rstart = heightSize-1;
	int count = 0;
	int i;
	int lheight, rheight, mheight;
	while (lstart < rstart) {
		/* adjust left bound */
		while (height[lstart] <= 0 && lstart < rstart) {
			lstart++;
		}
		lheight = height[lstart];
		/* adjust right bound */
		while (height[rstart] <= 0 && lstart < rstart) {
			rstart--;
		}
		rheight = height[rstart];
		mheight = min(lheight, rheight);
		height[lstart] -= mheight;
		height[rstart] -= mheight;
		for (i = lstart+1; i < rstart; i++) {
			count += max(mheight - max(height[i], 0), 0);
			height[i] -= mheight;
		}
	}
	return count;
}
