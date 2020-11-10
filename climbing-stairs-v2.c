
int memo[46];

/* memoized divide and conquer */
int
climbStairs(int n)
{
	if (n < 3) {
		return n;
	}
	if (memo[n] == 0) {
		memo[n] =  climbStairs(n-1) + climbStairs(n-2);
	}
	return memo[n];
}
