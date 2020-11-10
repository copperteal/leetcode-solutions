#include <stdlib.h>

bool isPalindrome(int x){
	if (x < 0)
		return false;

	int digits_size = 32;
	int *digits = (int*)malloc(digits_size*sizeof(int));
	int r = 0;

	while (x != 0) {
		digits[r] = x % 10;
		x /= 10;
		if (++r == digits_size) {
			digits_size *= 2;
			digits = (int*)realloc(digits, digits_size*sizeof(int));
		}
	}

	r--;
	int l;
	for (l = 0; l < r && digits[l] == digits[r]; l++, r--)
		;
	free(digits);
	if (l < r)
		return false;
	return true;
}
