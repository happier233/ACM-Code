// 普通素数筛
const int PMAX = 1000000;

int prime_count = 0;
bool prime_list[PMAX] = { false };//元素值为0代表是素数
int prime_table[PMAX] = { 0 };

void initPrime() {
    for (int i = 2; i < PMAX; i++) {
        if (!prime_list[i])
            prime_table[prime_count++] = i;
        for (int j = 0, e = PMAX / i;
             j < prime_count && prime_table[j] <= e; j++) {
            prime_list[i * prime_table[j]] = true;
            if (i % prime_table[j] == 0) break;
        }
    }
}


// 可以得到其中一个质因子的素数筛
const int PMAX = 1000005;

int prime_count = 0;
int prime_list[PMAX] = {0}; //元素值为0代表是素数
int prime_table[PMAX] = {0};

void initPrime() {
    for (int i = 2; i < PMAX; i++) {
        if (!prime_list[i])
            prime_list[i] = prime_table[prime_count++] = i;
        for (int j = 0, e = PMAX / i, now; 
        	j < prime_count && (now = prime_table[j]) <= e; j++) {
            prime_list[i * now] = now;
            if (i % now == 0) break;
        }
    }
}