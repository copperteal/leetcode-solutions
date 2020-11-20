/* dynamic programming
 * 4 ms
 * 92.68%
 * 64.63%
 */
#define min(X,Y) ((X) < (Y) ? (X) : (Y))


int
minCostClimbingStairs(int* cost, int costSize)
{
	/* index == number of steps remaining */
	/* entry == min cost */
	int solutions[costSize+1];
	solutions[0] = 0;
	solutions[1] = 0;
	int i;
	for (i = 2; i <= costSize; i++) {
		solutions[i] = min(solutions[i-1] + cost[costSize-i],
		solutions[i-2] + cost[costSize-i+1]);
	}
	return solutions[costSize];
}
