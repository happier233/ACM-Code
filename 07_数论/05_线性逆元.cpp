// 逆元，阶乘，阶乘逆元
ll inv[N] = {1, 1}, fac[N] = {1, 1}, ifac[N] = {1, 1};
// 线性求逆元
void init() {
	// 如果用的Int记得下面inv[i] = 1ll*...
    for (int i = 2; i < N; i++) {
        inv[i] = (MOD - (MOD / i)) * inv[MOD % i] % MOD;
        fac[i] = fac[i - 1] * i % MOD;
        ifac[i] = ifac[i - 1] * inv[i] % MOD;
    }
}