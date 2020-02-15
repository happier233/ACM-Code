const int N = int(1e6 + 48);
const int MOD = 998244353;
const int pr = 3;
const int phi = MOD - 1;
const int sq2 = 116195171; 

int fpow(ll a, ll k) {
    ll c = 1;
    for (; k; k >>= 1) {
        if (k & 1) (c *= a) %= MOD;
        (a *= a) %= MOD;
    }
    return c;
}

int calc(int n) {
    int k = 0;
    while ((1 << k) < n) k++;
    return k;
}

int rk[N], rn = 0;

template<class T>
void change(T p[], int n) {
    int k = calc(n);
    if (rn != n) {
        rn = n;
        for (int i = 0; i < n; i++) rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (k - 1));
    }
    for (int i = 0; i < n; i++) if (i < rk[i]) swap(p[i], p[rk[i]]);
}

// FFT
const double pi = acos(-1.0);
using Complex = complex<double>;

void FFT(Complex p[], int n, int opt) {
    change(p, n);
    for (int i = 1; i < n; i <<= 1) { //待合并区间的长度的一半
        Complex wn(cos(pi / i), opt * sin(pi / i)); //单位根
        for (int R = i << 1, j = 0; j < n; j += R) { //R是区间的长度，j表示前已经到哪个位置了
            Complex w(1, 0); //幂
            for (int k = 0; k < i; ++k, w = w * wn) { //枚举左半部分
                Complex x = p[j + k], y = w * p[j + i + k]; //蝴蝶效应
                p[j + k] = x + y;
                p[j + i + k] = x - y;
            }
        }
    }
}

void NTT(ll p[], int n, int opt) {
    change(p, n);
    for (int i = 1; i < n; i <<= 1) {
        ll wn = fpow(pr, phi / (i << 1));
        for (int R = i << 1, j = 0; j < n; j += R) {
            ll w = 1;
            for (int k = 0; k < i; ++k, w = w * wn % MOD) {
                ll x = p[j + k], y = w * p[i + j + k] % MOD;
                p[j + k] = (x + y) % MOD;
                p[i + j + k] = (x - y + MOD) % MOD;
            }
        }
    }
    if (opt == -1)reverse(p + 1, p + n);
}