int fast_pow(int a, int b) {
	//a %= 1000;
	int r = 1, base = a;
	while (b) {
		if (b & 1) {
			r *= base;
			//r %= 1000;
		}
		base *= base;
		//base %= 1000;
		b >>= 1;
	}
	return r;
}
