

template <class T>
inline bool read(T &x) {
    x = 0;
    char c = getchar();
	if(c == EOF) return false;
    bool f = false;
    for (; !isdigit(c); c = getchar()) f ^= (c == '-');
    for (; isdigit(c); c = getchar()) x = x * 10 + (c - '0');
    x = f ? -x : x;
	return true;
}
 
template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + '0');
}