/* greedy
 * 4 ms
 * 96.58%
 * 38.90%
 */

int
maxProfit(int* prices, int pricesSize)
{
  int profit = 0;
  int i;
  for (i = 1; i < pricesSize; i++) {
    if (prices[i] > prices[i-1]) {
      profit += prices[i] - prices[i-1];
    }
  }
  return profit;
}
