int romanToInt(char * s){
	int val = 0;
	int c, p;

	p = '\0';
	while ((c = *s) != '\0') {
		switch (c) {
		case 'I':
			val += 1;
			break;
		case 'V':
			val += (p == 'I') ? 3 : 5;
			break;
		case 'X':
			val += (p == 'I') ? 8 : 10;
			break;
		case 'L':
			val += (p == 'X') ? 30 : 50;
			break;
		case 'C':
			val += (p == 'X') ? 80 : 100;
			break;
		case 'D':
			val += (p == 'C') ? 300 : 500;
			break;
		case 'M':
			val += (p == 'C') ? 800 : 1000;
			break;
		}
		p = c;
		s++;
	}
	return val;
}
