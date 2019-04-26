#define prime_max 1000000

int prime_count = 0;
bool prime_list[prime_max] = { false };//元素值为0代表是素数
int prime_table[prime_max] = { 0 };

void initPrime() {
    for (int i = 2; i < prime_max; i++) {
        if (!prime_list[i])
            prime_table[prime_count++] = i;
        for (int j = 0, e = prime_max / i;
             j < prime_count && prime_table[j] <= e; j++) {
            prime_list[i * prime_table[j]] = 1;
            if (i % prime_table[j] == 0) break;
        }
    }
}