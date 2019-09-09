inline int lowbit(int x) { return x & -x; }

int calc(int n) {
    int k = 0;
    while ((1 << k) < n) k++;
    return k;
}

// FFT
const double pi = acos(-1.0);

const int N = (1 << 20);
using Complex = complex<double>;

void change(Complex p[], int n) {
    int k = calc(n);
    n = 1 << k;
    vector<int> r(n, 0);
    for (int i = 0; i < n; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int i = 0; i < n; i++) if (i < r[i]) swap(p[i], p[r[i]]);
}

void FFT(Complex p[], int n, int type) {
    change(p, n);
    for (int mid = 1; mid < n; mid <<= 1) { //待合并区间的长度的一半
        Complex wn(cos(pi / mid), type * sin(pi / mid)); //单位根
        for (int R = mid << 1, j = 0; j < n; j += R) { //R是区间的长度，j表示前已经到哪个位置了
            Complex w(1, 0); //幂
            for (int k = 0; k < mid; k++, w = w * wn) { //枚举左半部分
                Complex x = p[j + k], y = w * p[j + mid + k]; //蝴蝶效应
                p[j + k] = x + y;
                p[j + mid + k] = x - y;
            }
        }
    }
}