
/* bitshift recursion */
int
mySqrt(int x)
{
	if (x < 2)
		return x;

	/* sqrt(x) = 2*sqrt(x/4) */
	int approx = (mySqrt(x>>2)<<1) + 1;
	return (long) approx * approx > x ? approx-1 : approx;
}
