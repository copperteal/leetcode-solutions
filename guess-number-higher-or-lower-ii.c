/* brute force: dynamic programming
 * 40 ms
 * 87.50%
 * 50.00%
 */
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

int
getMoneyAmount(int n)
{
  int mincost[n+1][n+1];
  int i, j;
  /* no cost for picking the sole element */
  for (i = 1; i <= n; i++) {
    mincost[i][i] = 0;
  }
  /* pick the cheaper of two elements */
  for (i = 1; i < n; i++) {
    mincost[i][i+1] = i;
  }
  int cost, len;
  for (len = 2; len < n; len++) {
    for (i = 1; i+len <= n; i++) {
      mincost[i][i+len] = i + mincost[i+1][i+len];
      for (j = i+1; j < i+len; j++) {
        cost = j + max(mincost[i][j-1], mincost[j+1][i+len]);
        if (mincost[i][i+len] > cost) {
          mincost[i][i+len] = cost;
        }
      }
    }
  }

  return mincost[1][n];
}
