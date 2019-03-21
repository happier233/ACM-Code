int gcd(int x, int y) {
	int t;
	while (y){
		t = x % y;
		x = y;
		y = t;
	}
	return  x;
}