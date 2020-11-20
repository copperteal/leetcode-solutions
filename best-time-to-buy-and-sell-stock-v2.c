/* single pass
 * 4 ms
 * 95.79%
 * 33.04%
 */


int
maxProfit(int* prices, int pricesSize)
{
  if (pricesSize < 2) {
    return 0;
  }

  int i, minprice, maxprofit;
  for (i = 0, minprice = prices[0], maxprofit = 0; i < pricesSize; i++) {
    if (prices[i] < minprice) {
      minprice = prices[i];
    } else if (prices[i] - minprice > maxprofit) {
      maxprofit = prices[i] - minprice;
    }
  }
  return maxprofit;
}
