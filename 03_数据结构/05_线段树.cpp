// hdu 6562
struct TreeNode {
    int l, r;
    int lson, rson;
    ll sum;
    ll len;
    ll laz1, laz2, laz3;

    inline void init(int a, int b, int ls, int rs) {
        lson = ls;
        rson = rs;
        l = a, r = b;
        sum = 0;
        len = 1;
        laz1 = laz2 = 0;
        laz3 = 1;
    }

    inline int mid() {
        return (l + r) >> 1;
    }

    inline int width() {
        return r - l + 1;
    }

    inline void add(ll val) {
        sum = (sum * 10 + val * len * 10 + val * width()) % MOD;
        len = (len * 100) % MOD;
        // 右懒惰
        laz1 = (laz1 * 10 + val) % MOD;
        // 左懒惰
        laz2 = (laz2 + val * laz3) % MOD;
        // 长度懒惰
        laz3 = (laz3 * 10) % MOD;
    }
};

struct SegTree {
    int tot;
    TreeNode node[N << 1];

    inline void init() {
        tot = 0;
    }

    inline void up(int k) {
        TreeNode &nd = node[k];
        nd.sum = (node[nd.lson].sum + node[nd.rson].sum) % MOD;
        nd.len = (node[nd.lson].len + node[nd.rson].len) % MOD;
    }

    inline void push(int k) {
        TreeNode &nd = node[k];
        if (nd.laz3 == 1) return;
        TreeNode &lson = node[nd.lson];
        TreeNode &rson = node[nd.rson];

        lson.sum = (nd.laz1 * lson.width() + lson.sum * nd.laz3 + nd.laz2 * lson.len % MOD * nd.laz3) % MOD;
        lson.len = (lson.len * nd.laz3 % MOD * nd.laz3) % MOD;
        lson.laz1 = (lson.laz1 * nd.laz3 + nd.laz1) % MOD;
        lson.laz2 = (nd.laz2 * lson.laz3 + lson.laz2) % MOD;
        lson.laz3 = (lson.laz3 * nd.laz3) % MOD;

        rson.sum = (nd.laz1 * rson.width() + rson.sum * nd.laz3 + nd.laz2 * rson.len % MOD * nd.laz3) % MOD;
        rson.len = (rson.len * nd.laz3 % MOD * nd.laz3) % MOD;
        rson.laz1 = (rson.laz1 * nd.laz3 + nd.laz1) % MOD;
        rson.laz2 = (nd.laz2 * rson.laz3 + rson.laz2) % MOD;
        rson.laz3 = (rson.laz3 * nd.laz3) % MOD;

        nd.laz1 = nd.laz2 = 0;
        nd.laz3 = 1;
    }

    void build(int k, int l, int r) {
        TreeNode &nd = node[k];
        nd.init(l, r, tot + 1, tot + 2);
        tot += 2;
        if (l == r) {
            return;
        }
        int mid = nd.mid();
        build(nd.lson, nd.l, mid);
        build(nd.rson, mid + 1, nd.r);
        up(k);
    }

    void change(int k, int l, int r, ll val) {
        TreeNode &nd = node[k];
        if (nd.l == l && nd.r == r) {
            nd.add(val);
            return;
        }
        push(k);
        int mid = nd.mid();
        if (r <= mid) {
            change(nd.lson, l, r, val);
        } else if (l > mid) {
            change(nd.rson, l, r, val);
        } else {
            change(nd.lson, l, mid, val);
            change(nd.rson, mid + 1, r, val);
        }
        up(k);
    }

    ll query(int k, int l, int r) {
        TreeNode &nd = node[k];
        if (nd.l == l && nd.r == r) {
            return nd.sum;
        }
        push(k);
        int mid = nd.mid();
        ll ans = 0;
        if (r <= mid) {
            ans += query(nd.lson, l, r);
        } else if (l > mid) {
            ans += query(nd.rson, l, r);
        } else {
            ans += query(nd.lson, l, mid);
            ans += query(nd.rson, mid + 1, r);
        }
        return ans % MOD;
    }
} tree;