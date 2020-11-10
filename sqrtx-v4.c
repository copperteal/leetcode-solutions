
/* binary search */
int
mySqrt(int x)
{
	if (x < 2)
		return x;

	int left = 2;
	int right = x/2;
	int mid;
	while (left <= right) {
		mid = (left+right)/2;
		if ((long)mid*mid < x) {
			left = mid+1;
		} else {
			right = mid-1;
		}
	}
	return (long) left * left <= x ? left : right;
}
