char * my_itoa(int value, char* result, int base = 10);

char * my_itoa(int value, char* result, int base) {
	// check that the base if valid  

	if (base < 2 || base > 16) { *result = 0; return result; }
	char* out = result;
	int quotient = abs(value);
	do {
		const int tmp = quotient / base;
		*out = "0123456789abcdef"[quotient - (tmp*base)];
		++out;
		quotient = tmp;
	} while (quotient);
	// Apply negative sign  
	if (value < 0) *out++ = '-';
	std::reverse(result, out);
	*out = 0;
	return result;
}