

/* Sliding Window with pointers */
int lengthOfLastWord(char * s){
	/* strip leading blanks */
	while (*s == ' ')
		s++;
	/* trivial case */
	if (*s == '\0')
		return 0;

	int l = 1;
	char *t = s;
	while (*(++s) != '\0') {
		if (*s == ' ') {
			l = (t < s) ? s-t : l;
			t = s + 1;
		}

	}
	/* account for trailing blanks */
	return (t < s) ? s-t : l;
}
