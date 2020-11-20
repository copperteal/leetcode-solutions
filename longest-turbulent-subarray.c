/* single pass
 * 60 ms
 * 100.00%
 * 50.00%
 */
#define OUT 0
#define IN 1


int
maxTurbulenceSize(int* arr, int arrSize)
{
  if (arrSize < 2) {
    return arrSize;
  }

  int len = 0;
  int max = (arr[0] != arr[1]) ? 2 : 1;
  int i;
  int state = OUT;
  for (i = 2; i < arrSize; i++) {
    if (arr[i-2] < arr[i-1] && arr[i-1] > arr[i]) {
      len++;
      if (state == OUT) {
        len += 2;
        state = IN;
      }
    } else if (arr[i-2] > arr[i-1] && arr[i-1] < arr[i]) {
      len++;
      if (state == OUT) {
        len += 2;
        state = IN;
      }
    } else {
      state = OUT;
      if (max < len) {
        max = len;
      }
      len = 0;
    }
  }
  return (max > len) ? max : len;
}
