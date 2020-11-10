/* 4ms
 * 86.30%
 * 37.44%
 */
#define min(A,B) ((A) < (B) ? (A) : (B))


/* stack version */
int
trap(int* height, int heightSize)
{
	if (heightSize < 3) {
		return 0;
	}

	int count = 0;
	int stack[heightSize+1];
	stack[0] = 0;
	int top = 1;
	int peekl;
	int peekr;
	int dist;
	int next = 0;
	while (next < heightSize) {
		peekr = stack[top-1];
		while (height[peekr] < height[next]) {
			top--;
			if (top < 1) {
				break;
			}
			peekl = stack[top-1];
			if (height[peekr] <= height[peekl]) {
				dist = next - peekl - 1;
				count += (min(height[peekl], height[next]) - height[peekr])*dist;
				peekr = stack[top-1];
			} else {
				break;
			}
		}
		stack[top++] = next++;
	}
	return count;
}
