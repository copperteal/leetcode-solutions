

/* dynamic programming */
int
climbStairs(int n)
{
	if (n < 3) {
		return n;
	}
	int dp[n+1];
	int i;
	for (i = 0; i < 3; i++)
		dp[i] = i;
	for (i = 3; i < n+1; i++)
		dp[i] = dp[i-1] + dp[i-2];
	return dp[n];
}
