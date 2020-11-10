

/* Brute-Force */
int strStr(char * haystack, char * needle){
	if (needle[0] == '\0')
		return 0;
	if (haystack[0] == '\0')
		return -1;

	int i, j;
	for (i = 0; haystack[i] != '\0'; i++) {
		for (j = 0; needle[j] == haystack[i+j] && needle[j] != '\0'; j++)
			;
		if (needle[j] == '\0')
			return i;
	}
	return -1;
}
