/* 20ms
 * 62.56%
 * 5.13%
 */
#include <string.h>


/* odd vs even partition */
char *
longestPalindrome(char * s)
{
	if (s[0] == '\0' || s[1] == '\0') {
		return s;
	}

	int L = strlen(s);
	int ans[2] = { 0, 0};
	int max = 1;
	int i, j, k;
	/* look for odd palindromes centered at i */
	for (i = 1; i < L-1; i++) {
		for (j = 1; i >= j && i+j < L && s[i-j] == s[i+j]; j++)
			;
		/* possible terminating conditions:
		 * 1) i < j
		 * 2) i+j == L
		 * 3) s[i-j] != s[i+j]
		 */
		j--;
		if (s[i-j] == s[i+j] && 2*j+1 > max) {
			max = 2*j+1;
			ans[0] = i-j;
			ans[1] = i+j;
		}
	}
	/* look for even palindromes centered right of i*/
	for (i = 0; i < L-1; i++) {
		for (j = 1; i >= j-1 && i+j < L && s[i-j+1] == s[i+j]; j++)
			;
		/* possible terminating conditions:
		 * 1) i+1 < j
		 * 2) i+j == L
		 * 3) s[i-j+1] != s[i+j]
		 */
		j--;
		if (s[i-j+1] == s[i+j] && 2*j > max) {
			max = 2*j;
			ans[0] = i-j+1;
			ans[1] = i+j;
		}
	}

	s[ans[1]+1] = '\0';
	return s + ans[0];
}
