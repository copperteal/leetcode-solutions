/* binary seach
 * 0 ms
 * 100.00%
 * 34.24%
 */
#include <stdbool.h>

// The API isBadVersion is defined for you.
// // bool isBadVersion(int version);
bool isBadVersion(int version);

int
firstBadVersion(int n)
{
  if (n < 2) {
    return n;
  }

  int low, mid, high;
  low = 1;
  high = n;
  while (low < high) {
    mid = high + (low-high)/2;
    if (isBadVersion(mid)) {
      high = mid-1;
    } else {
      low = mid+1;
    }
  }
  if (isBadVersion(low)) {
    return low;
  } else {
    return low+1;
  }
}
