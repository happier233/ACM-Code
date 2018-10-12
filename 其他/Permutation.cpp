// 错排问题
// D(n) = n! [(-1)^2/2! + … + (-1)^(n-1)/(n-1)! + (-1)^n/n!].
long long table[1000] = {0, 0, 1};
void init() {
    for (int i = 3; i <= 20; i++) {
        table[i] = (i - 1) * (table[i - 1] + table[i - 2]);
    }
}