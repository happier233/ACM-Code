const int N = 100005;
int f[N], deep[N], d[N];

void init(int n) {
    for (int i = 0; i <= n; i++) f[i] = i, d[i] = 0;
}

int fa(int x) {
    if (f[x] == x) return x;
    int fx = fa(f[x]);
    (d[x] += d[f[x]]) %= 3;
    return f[x] = fx;
}

bool un(int x, int y, int dis) {
    int fx = fa(x), fy = fa(y);
    if (fx == fy) {
        return ((d[y] - d[x] + 3) % 3 != dis);
    }
    int w = (3 + (d[x] - d[y]) + dis) % 3;
    // 按轶合并
    if (deep[fx] < deep[fy]) {
        swap(fx, fy);
        w = (3 - w) % 3;
    }
    f[fy] = fx;
    d[fy] = w;
    // 按轶合并
    deep[fx] += deep[fx] == deep[fy];
    return true;
}