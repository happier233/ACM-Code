void FWT(int p[], int n) { // 如果要取模运算记得-x+MOD,*inv
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += (i << 1)) {
            for (int k = 0; k < i; k++) {
                // or{
                p[i + j + k] += +p[j + k];
                // and
                p[j + k] += p[i + j + k];
                // xor
                tie(p[j + k], p[i + j + k]) = make_pair(p[j + k] + p[i + j + k], p[j + k] - p[i + j + k]);
            }
        }
    }
}

void IFWT(int p[], int n) { // 如果要取模运算记得-x+MOD,*inv
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += (i << 1)) {
            for (int k = 0; k < i; k++) {
                // or
                p[i + j + k] -= p[j + k];
                // and
                p[j + k] -= p[i + j + k];
                // xor
                tie(p[j + k], p[i + j + k]) = make_pair(p[j + k] + p[i + j + k], p[j + k] - p[i + j + k]);
                p[j + k] = p[j + k] / 2, p[i + j + k] = p[i + j + k] / 2;
            }
        }
    }
}