const int N = 50005;

struct SegTree {
    ll c[N];
    ll ans[N << 2];
    ll laz[N << 2];

    void init(int n) {
        memset(c, 0, sizeof(ll) * (n + 1));
    }

    inline void up(int k) {
        ans[k] = ans[k << 1] + laz[k << 1] + ans[k << 1 | 1] + laz[k << 1 | 1];
    }

    inline void push(int k) {
        laz[k << 1] += laz[k];
        laz[k << 1 | 1] += laz[k];
        ans[k] += laz[k];
        laz[k] = 0;
    }

    void build(int x, int y, int k) {
        laz[k] = 0;
        if (x == y) {
            ans[k] = c[x];
            return;
        }
        int m = (x + y) >> 1;
        build(x, m, k << 1);
        build(m + 1, y, k << 1 | 1);
        up(k);
    }

    void change(int x, int y, int k, int l, int r, ll v) {
        if (x == l && y == r) {
            laz[k] += v;
            return;
        }
        push(k);
        int m = (x + y) >> 1;
        if (r <= m) change(x, m, k << 1, l, r, v);
        else if (l > m)change(m + 1, y, k << 1 | 1, l, r, v);
        else change(x, m, k << 1, l, m, v), change(m + 1, y, k << 1 | 1, m + 1, r, v);
        up(k);
    }

    ll query(int x, int y, int k, int l, int r) {
        if (x == l && y == r) {
            return ans[k] + laz[k];
        }
        int m = (x + y) >> 1;
        push(k);
        if (r <= m) return query(x, m, k << 1, l, r);
        else if (l > m) return query(m + 1, y, k << 1 | 1, l, r);
        else return query(x, m, k << 1, l, m) + query(m + 1, y, k << 1 | 1, m + 1, r);
    }
};