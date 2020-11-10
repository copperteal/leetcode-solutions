#include <stdbool.h>
#include <stdio.h>

int
main()
{
	if (true && false || true) {
		printf("&& first\n");
	} else {
		printf("|| first\n");
	}
}
