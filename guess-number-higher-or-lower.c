/* binary search
 * 0 ms
 * 100.00%
 * 54.63%
 */


/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return        -1 if num is lower than the guess number
 *            1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */
int guess(int num);

int
guessNumber(int n)
{
  if (n == 1) {
    return 1;
  }
  int low, high, mid;
  for (low = 0, high = n, mid = (low+high)/2;
  low < high; mid = high+(low-high)/2) {
    if (guess(mid) < 0) {
      high = mid-1;
    } else if (guess(mid) > 0) {
      low = mid+1;
    } else {
      return mid;
    }
  }
  return mid;
}
