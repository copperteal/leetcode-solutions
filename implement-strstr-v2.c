#define MODULUS 101
#define BASE    33


/* Rabin-Karp Algorithm */
int rkhash(char *s, int l);


int strStr(char * haystack, char * needle){
	/* trivial cases */
	if (needle[0] == '\0')
		return 0;
	if (haystack[0] == '\0')
		return -1;

	/* get lengths */
	int nl;
	for (nl = 0; needle[nl] != '\0'; nl++)
		;
	int hl;
	for (hl = 0; haystack[hl] != '\0'; hl++)
		;
	/* needle too long */
	if (nl > hl)
		return -1;

	/* needle hash */
	int nh = rkhash(needle, nl);
	/* lead char */
	char lc = needle[0];

	int j;
	int i = 0;
	while (haystack[i+nl-1] != '\0') {
		if (haystack[i] == lc && rkhash((haystack+i), nl) == nh) {
			for (j = 0; j < nl; j++) {
				if (needle[j] != haystack[i+j])
					break;
			}
			if (j == nl)
				return i;
		}
		i++;
	}
	return -1;
}

/* Rabin-Karp algorithm */
int
rkhash(char *s, int l)
{
	int i, t;
	t = 0;

	for (i = 0; i < l; i++, s++)
		t = (t * BASE + *s) % MODULUS;
	return t;
}
