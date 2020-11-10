/* 1248 ms
*  * 100.00%
*   * 44.87%
*    */

int
getSum(int a, int b)
{
	int c;
	if (b < 0) {
		for (c = a; b < 0; b++, c--)
			;
	} else {
		for (c = a; b > 0; b--, c++)
			;
	}
	return c;
}
