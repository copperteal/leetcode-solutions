

/* brute force */
int mySqrt(int x){
	if (x == 0)
		return 0;

	int s;
	for (s = 1; s <= x / s; s++)
		;
	return s-1;
}
