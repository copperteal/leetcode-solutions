

int
twoSumLessThanK(int* A, int ASize, int K)
{
	int lo = 1;
	int hi = 0;
	int i;
	for (i = 0; i < ASize; i++) {
		if (A[i] > hi) {
			hi = A[i];
		}
	}
	int count[hi+1];
	for (i = 0; i <= hi; i++) {
		count[i] = 0;
	}
	for (i = 0; i < ASize; i++) {
		count[A[i]]++;
	}
	int max = -1;
	while (lo <= hi) {
		if (K <= lo+hi) {
			hi--;
		} else if (count[hi] == 0) {
			hi--;
		} else if (count[lo] == 0) {
			lo++;
		} else if (lo == hi) {
			if (count[lo] > 1) {
				max = (lo+hi > max) ? lo+hi : max;
			}
			lo++;
		} else {
			max = (lo+hi > max) ? lo+hi : max;
			lo++;
		}
	}
	return max;
}
