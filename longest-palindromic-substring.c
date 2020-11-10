/* 192 ms
 * 31.29%
 * 5.10%
 */
#include <stdbool.h>
#include <string.h>


/* dynamic programming */
char *
longestPalindrome(char * s)
{
	if (s[0] == '\0' || s[1] == '\0') {
		return s;
	}

	int L = strlen(s);
	bool A[L][L];
	int ans[2] = { 0, 0 };
	int max = 1;
	int i, j;
	A[0][0] = true;
	for (i = 1; i < L; i++) {
		A[i][i] = true;
		A[i-1][i] = (s[i-1] == s[i]);
		if (A[i-1][i] && max == 1) {
			ans[0] = i-1;
			ans[1] = i;
			max = 2;
		}
	}

	for (j = 2; j < L; j++) {
		for (i = 0; i < j-1; i++) {
			A[i][j] = A[i+1][j-1] && s[i] == s[j];
			if (A[i][j] && max + i < j + 1) {
				ans[0] = i;
				ans[1] = j;
				max = j - i + 1;
			}
		}
	}
	s[ans[1]+1] = '\0';
	return s+ans[0];
}
