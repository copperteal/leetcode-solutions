#include <math.h>

/* math library */
int mySqrt(int x){
	if (x < 2) return x;
	int ceil =  (int)exp(log(x)*0.5) + 1;
	return (long) ceil * ceil > x ? ceil-1 : ceil;
}
