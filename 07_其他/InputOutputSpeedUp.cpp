//适用于正负整数
template <class T>
inline bool scan_d (T &ret) {
    char c; int sgn;
    if( c = getchar(), c == EOF)    return 0; //EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}
inline void out (int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
    if (x > 9) out (x / 10);
    putchar (x % 10 + '0');
}
inline void out(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	char list[100];
	int now = 0;
	while (x > 9) {
		list[++now] = (x % 10 + '0');
		x /= 10;
	}
	putchar(x + '0');
	while (now) {
		putchar(list[now--]);
	}
}