/* calculate left and right max profits separately, then combine.
 * 120 ms
 * 75.61%
 * 48.78%
 */


int
maxProfit(int* prices, int pricesSize)
{
  if (pricesSize < 2) {
    return 0;
  }

  int i;
  int left[pricesSize];
  left[0] = 0;
  int leftmin = prices[0];
  int right[pricesSize];
  right[pricesSize-1] = 0;
  int rbound = pricesSize-1;
  int rightmax = prices[rbound];
  for (i = 1; i < pricesSize; i++) {
    if (leftmin > prices[i]) {
      leftmin = prices[i];
    }
    if (left[i-1] + leftmin < prices[i]) {
      left[i] = prices[i] - leftmin;
    } else {
      left[i] = left[i-1];
    }

    rbound = pricesSize-1-i;
    if (rightmax < prices[rbound]) {
      rightmax = prices[rbound];
    }
    if (right[rbound+1] + prices[rbound] < rightmax) {
      right[rbound] = rightmax - prices[rbound] ;
    } else {
      right[rbound] = right[rbound+1];
    }
  }
  /* find max */
  int max = 0;
  for (i = 0; i < pricesSize-1; i++) {
    if (left[i] + right[i+1] > max) {
      max = left[i] + right[i+1];
    }
  }

  /* edge cases */
  if (right[0] > max) {
    return right[0];
  } else if (left[pricesSize-1] > max) {
    return left[pricesSize-1];
  } else {
    return max;
  }
}
