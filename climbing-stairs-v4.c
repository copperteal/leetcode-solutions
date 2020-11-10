

/* Fibonacci Numbers */
int
climbStairs(int n)
{
	if (n < 3) {
		return n;
	}
	int i, a = 1, b = 2;
	int c;
	for (i = 3; i <= n; i++) {
		c = a+b;
		a = b;
		b = c;
	}
	return b;
}
