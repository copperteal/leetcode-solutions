/* incremental pointer
 * 0 ms
 * 100.00%
 * 70.41%
 */
#include <limits.h>

int
myAtoi(char * s)
{
	for ( ; *s == ' '; s++)
		;
	if (*s == '\0') {
		return 0;
	}

	int sign = (*s == '-') ? 1 : 0;
	if (*s == '-' || *s == '+') {
		s++;
	}

	int out;
	for (out = 0; '0' <= *s && *s <= '9'; s++) {
		if (out > (INT_MAX - *s + '0') / 10) {
			if (sign) {
				return INT_MIN;
			} else {
				return INT_MAX;
			}
		}
		out *= 10;
		out += *s - '0';
	}
	return sign ? -out : out;
}
