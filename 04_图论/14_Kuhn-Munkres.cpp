const int N = 1005;
const ll INF = ll(2e11);

ll cost[N][N];
// lx, ly 表示当前期望值, slack是得到链接的期望值
ll lx[N], ly[N], slack[N];
// prey->alternating tree, match是y->x的链接
int prey[N], match[N];
bool vy[N]; // 是否已经变化的点

void augment(int n, int root) {
    fill_n(vy + 1, n, false);
    fill_n(slack + 1, n, INF);
    int py = 0;
    match[py] = root;
    do {
        vy[py] = true;
        int x = match[py], yy = 0;
        ll delta = INF;
        for (int y = 1; y <= n; y++) {
            if (vy[y]) continue;
            ll w = lx[x] + ly[y] - cost[x][y];
            if (w < slack[y])
                slack[y] = w, prey[y] = py;
            if (slack[y] < delta) delta = slack[y], yy = y;
        }
        for (int y = 0; y <= n; y++) {
            if (vy[y])
                lx[match[y]] -= delta, ly[y] += delta;
            else
                slack[y] -= delta;
        }
        py = yy;
    } while (match[py] != -1);
    do {
        int pre = prey[py];
        match[py] = match[pre], py = pre;
    } while (py);
}

ll KM(int n) {
    fill_n(match + 1, n, -1);
    fill_n(ly + 1, n, 0);
    for (int i = 1; i <= n; i++) {
        lx[i] = *max_element(cost[i] + 1, cost[i] + n + 1);
    }
    ll ans = 0;
    for (int root = 1; root <= n; root++) augment(n, root);
    for (int i = 1; i <= n; i++) ans += lx[i], ans += ly[i];
    return ans;
}