#include <stdlib.h>
#include <string.h>

void reverse(char *);

char*
addBinary(char * a, char * b)
{
	if (*a == '0') {
		return b;
	} else if (*b == '0') {
		return a;
	}

	int al = strlen(a);
	int bl = strlen(b);
	/* ensure that b is not shorter than a */
	if (al > bl) {
		int templ = al;
		al = bl;
		bl = templ;
		char *tempp = a;
		a = b;
		b = tempp;
	}
	char *c = (char*) calloc(bl+2, sizeof(char));
	char *cp = c;
	int carr = 0;

	/* position pointers at one's digit */
	for (a += al -1, b += bl -1;
	al > 0; al--, bl--) {
		*cp = (*a-- - '0') + (*b-- - '0') + carr;
		carr = *cp >> 1;
		*cp = (*cp & 1) + '0';
		cp++;
	}
	for ( ; bl > 0; bl--) {
		*cp = (*b-- - '0') + carr;
		carr = *cp >> 1;
		*cp = (*cp & 1) + '0';
		cp++;
	}

	if (carr) {
		*cp++ = carr + '0';
	}
	*cp = '\0';
	reverse(c);
	return c;
}


void
reverse(char *b)
{
	char temp;
	int i, j;
	for (i = 0, j = strlen(b)-1; i < j; i++, j--) {
		temp = b[i];
		b[i] = b[j];
		b[j] = temp;
	}
}
