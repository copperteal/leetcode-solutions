#define INTMAXPOS 2147483647
#define INTMAXDIV 214748364
#define INTMAXNEG 2147483648

int reverse(int x){
	int sign = (x < 0) ? -1 : 1;
	int digit;
	int reversed = 0;

	if (sign < 0) {
		digit = -(x % 10);
		reversed *= 10;
		reversed += digit;
		x /= 10;
		x = -x;
	}

	while (x != 0) {
		digit = x % 10;
		if (reversed > INTMAXDIV)
			return 0;
		reversed *= 10;
		if (sign == 1 && reversed > INTMAXPOS - digit)
			return 0;
		if (sign == -1 && reversed > INTMAXNEG - digit)
			return 0;
		reversed += digit;
		x /= 10;
	}
	return sign * reversed;
}
