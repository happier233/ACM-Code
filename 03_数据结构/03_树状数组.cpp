const int N = 1000005;
struct BITree {
    int n;
    ll c[N];

    void init(int _n) {
        n = _n + 1;
        memset(c, 0, sizeof(ll) * n);
    }

    void change(int pos, ll v) {
        for (int i = pos; i < n; i += i & (-i))
            c[i] += v;
    }

    ll query(int x) {
        ll ans = 0;
        for (int i = x; i > 0; i -= i & (-i))
            ans += c[i];
        return ans;
    }

    void update(int l, int r, ll v) {
        change(l, v);
        change(r + 1, -v);
    }
} tree;

// 区间更新区间查询
struct BITree {
    int n;
    ll c[N], d[N];

    void init(int _n) {
        n = _n + 1;
        memset(c, 0, sizeof(ll) * n);
        memset(d, 0, sizeof(ll) * n);
    }

    void change(int pos, ll v) {
        for (int i = pos; i < n; i += i & (-i))
            c[i] += v, d[i] += v * (pos - 1);
    }

    ll query(int x) {
        ll ans = 0;
        for (int i = x; i > 0; i -= i & (-i))
            ans += x * c[i] - d[i];
        return ans;
    }

    void update(int l, int r, ll v) {
        change(l, v);
        change(r + 1, -v);
    }

    ll sum(int l, int r) {
        return query(r) - query(l - 1);
    }
} tree;