const int N = 2005;

struct TdBITree {
    int n, m;
    ll c[N][N];

    void init(int n, int m) {
        this->n = n;
        this->m = m;
        memset(c, 0, sizeof(c))
    }

    inline int lowbit(const int &x) {
        return x & -x;
    }

    void init(int n, int m, ll v) {
        this->n = n;
        this->m = m;
        rep(x, 1, N) {
            rep(y, 1, N) {
                c[x][y] = (x * y + (x - lowbit(x)) * (y - lowbit(y)) - x * (y - lowbit(y)) - (x - lowbit(x)) * y) * v;
            }
        }
    }

    int change(int x, int y, ll v) {
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= m; j += lowbit(j))
                c[i][j] += v;
        return 0;
    }

    ll query(int x, int y) {
        ll ans = 0;
        for (int i = x; i >= 1; i -= lowbit(i))
            for (int j = y; j >= 1; j -= lowbit(j))
                ans += c[i][j];
        return ans;
    }

    ll solve(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};