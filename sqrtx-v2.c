

/* Newton's Method */
double newton(double, int);

int
mySqrt(int x)
{
	if (x == 0)
		return 0;

	double lg = x / 2.0;
	double g = newton(lg, x);
	while ((int)(g-lg) != 0) {
		lg = g;
		g = newton(lg, x);
	}
	return g;
}

double
newton(double xn, int x)
{
	return (xn + x / xn) / 2;
}
