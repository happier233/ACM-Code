#include <cstring>
long long prime_max = 1000000;
bool prime_list_init = false;
bool * prime_list;
long long prime_count = 1;
long long * prime_table;

void initPrimeList(bool reload)
{
	if (reload) {
		delete[] prime_list;
		prime_list_init = false;
	}
	if (prime_list_init) {
		return;
	}
	prime_list = new bool[prime_max];
	memset(prime_list, true, sizeof(bool)*prime_max);
	prime_list[0] = false;
	prime_list[1] = false;
	long long max = prime_max / 2;
	for (long long  a = 2; a <= max; a++) {
		for (int b = 2; b <= a; b++) {
			long long s = a*b;
			if (s <= prime_max && s > 0) {
				prime_list[s] = false;
				prime_count++;
			}else{
				break;
			}
		}
	}
	prime_list_init = true;
}

void initPrimeTable(bool reload)
{
	if (!prime_list_init || reload) {
		initPrimeList(true);
	}
	prime_table = new long long[prime_count];
	int c = 0;
	for (int i = 2; i <= prime_max; i++) {
		if (prime_list[i]) {
			prime_table[c++] = i;
		}
	}
}