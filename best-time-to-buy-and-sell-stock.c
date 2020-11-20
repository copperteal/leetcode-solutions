/* lowest preceding price vs highest following price
 * 4ms
 * 95.79%
 * 47.65%
 */
#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))


int
maxProfit(int* prices, int pricesSize)
{
  if (pricesSize < 2) {
    return 0;
  }

  int i, j;
  int low[pricesSize];
  low[0] = prices[0];
  for (i = 1; i < pricesSize; i++) {
    low[i] = min(low[i-1], prices[i]);
  }
  int high[pricesSize];
  high[pricesSize-1] = prices[pricesSize-1];
  for (j = pricesSize-2; j >= 0; j--) {
    high[j] = max(high[j+1], prices[j]);
  }
  int max = 0;
  for (i = 0; i < pricesSize; i++) {
    if (high[i] > max + low[i]) {
      max = high[i] - low[i];
    }
  }
  return max;
}
