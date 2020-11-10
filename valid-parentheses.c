#include <stdlib.h>

bool isValid(char * s){
	int ssize = 8;
	int i = 0;
	char *stack = (char*) malloc(ssize*sizeof(char));

	char c;
	while ((c = *s) != '\0') {
		switch (c) {
		case '(':
		case '{':
		case '[':
			stack[i] = c;
			if (++i == ssize) {
				ssize *= 2;
				stack = (char*)realloc(stack, ssize*sizeof(char));
			}
			break;
		case ')':
			if (i <= 0 || stack[--i] != '(')
				return false;
			break;
		case '}':
			if (i <= 0 || stack[--i] != '{')
				return false;
			break;
		case ']':
			if (i <= 0 || stack[--i] != '[')
				return false;
			break;
		}
		s++;
	}
	if (i > 0)
		return false;
	free(stack);
	return true;
}
