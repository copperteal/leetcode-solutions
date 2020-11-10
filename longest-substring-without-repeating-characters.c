/* 4 ms
* * 84.34%
* * 7.68%
* */
#define TSIZE ('~' - ' ' + 1)


/* sliding window */
int
lengthOfLongestSubstring(char * s)
{
	if (*s == '\0') {
		return 0;
	} else if (s[1] == '\0') {
		return 1;
	}

	int i, j, k;
	int newi = 0;
	int len = 0;
	/* char -> index+1; keeps track of chars in substring */
	int table[TSIZE];
	for (i = 0; i < TSIZE; i++) {
		table[i] = 0;
	}
	for ( i = 0, j = 0 ; s[i] != '\0' ; i = newi ) {
		while (s[j] != '\0' && table[s[j] - ' '] == 0) {
			table[s[j] - ' '] = j + 1;
			j++;
		}
		len = (j > len + i) ? j - i : len;
		if (s[j] == '\0') {
			break;
		} else {
			newi = table[s[j] - ' '];
			for (k = i; k < newi; k++) {
				table[s[k] - ' '] = 0;
			}
		}
	}
	return len;
}

