/* 0 ms
 * 100.00%
 * 5.60%
 */
#include <stdlib.h>
#include <string.h>


/* left step, right step */
char *
convert(char * s, int numRows)
{
	if (numRows < 2) {
		return s;
	}
	int L = strlen(s);
	char *out = (char *)calloc(L+1, sizeof(char));
	int i, j, row, lstep, rstep;
	int gap = 2*numRows-2;
	i = 0;
	for (row = 0; row < numRows; row++) {
		j = row;
		rstep = 2*row;
		lstep = gap - rstep;
		while (i < L && j < L) {
			if (row != numRows-1) {
				out[i++] = s[j];
				j += lstep;
			}
			if (row && i < L && j < L) {
				out[i++] = s[j];
				j += rstep;
			}
		}
		if (i == L) {
			break;
		}
	}
	out[L] = '\0';
	return out;
}
