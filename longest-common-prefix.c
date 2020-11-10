#include <stdlib.h>
#include <string.h>

char * longestCommonPrefix(char ** strs, int strsSize)
{
	if (strsSize == 0) {
		char *returnString = (char*)malloc(sizeof(char));
		returnString[0] = '\0';
		return returnString;
	}

	char c;
	int i, j;

	i = j = 0;
	c = strs[0][0];
	while (true) {
		if (c == '\0') {
			break;
		} else if (++i == strsSize) {
			i = 0;
			j++;
			c = strs[i][j];
		} else if (c != strs[i][j]) {
			break;
		}
	}
	char *returnString = (char*)malloc((j+1)*sizeof(char));
	strncpy(returnString, *strs, j);
	returnString[j] = '\0';
	return returnString;
}
