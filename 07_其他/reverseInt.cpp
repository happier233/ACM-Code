template<typename T>

T reverseInt(T a)
{
	T b = 0;
	while (a != 0) {
		b *= 10;
		b += (a % 10);
		a /= 10;
	}
	return b;
}