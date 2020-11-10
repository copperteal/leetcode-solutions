#include <stdio.h>
#include <stdlib.h>


/* Single pass rescursive algorithm */
char * countAndSay(int n){
	if (n == 1) {
		char *output = (char*)malloc(2*sizeof(char));
		output[0] = '1';
		output[1] = '\0';
		return output;
	}

	char *input = countAndSay(n-1);
	/* input length */
	int il;
	for (il = 0; input[il] != '\0'; il++)
		;
	il++;
	char *output = (char*)malloc(2*il*sizeof(char));
	int i, j;
	int count;
	char c = input[0];
	j = count = 0;
	for (i = 0; i < il; i++) {
		if (c != input[i]) {
			j += sprintf((output+j), "%d", count);
			output[j++] = c;
			c = input[i];
			count = 1;
		} else {
			count++;
		}
	}
	output[j] = '\0';
	output = realloc(output, (j+1)*sizeof(char));
	free(input);
	return output;
}
