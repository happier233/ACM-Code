const int N = int(2e5 + 10);
const int MAXN = N * 150;

struct PArray {
    int tot = 0;
    struct node {
        int val, deep;
    } c[MAXN];
    int lson[MAXN], rson[MAXN];
    pii ran;

    int build(int l, int r) {
        int k = tot++;
        if (l == r) {
            c[k].val = l;
            return k;
        }
        int mid = (l + r) >> 1;
        lson[k] = build(l, mid);
        rson[k] = build(mid + 1, r);
        return k;
    }

    int init(int l, int r) {
        ran = {l, r};
        return build(l, r);
    }

    int update(int rt, int p, node w) {
        int l = ran.first, r = ran.second;
        int k = tot++, rst = k;
        while (l < r) {
            lson[k] = lson[rt], rson[k] = rson[rt];
            int mid = (l + r) >> 1;
            if (p <= mid) {
                rt = lson[rt];
                k = lson[k] = tot++;
                r = mid;
            } else {
                rt = rson[rt];
                k = rson[k] = tot++;
                l = mid + 1;
            }
        }
        c[k].val = w.val;
        c[k].deep = c[rt].deep + w.deep;
        return rst;
    }

    node query(int rt, int p) {
        int l = ran.first, r = ran.second;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (p <= mid) {
                rt = lson[rt];
                r = mid;
            } else {
                rt = rson[rt];
                l = mid + 1;
            }
        }
        return c[rt];
    }
};

struct PDSU {
    PArray tree;
    int root[N];

    void init(int n) {
        root[0] = tree.init(1, n);
    }

    PArray::node fa(int rt, int x) {
        PArray::node u = tree.query(root[rt], x);
        while (u.val != x) {
            x = u.val;
            u = tree.query(root[rt], x);
        }
        return u;
    }

    inline void change(int rt, int k) {
        root[k] = root[rt];
    }

    inline void un(int rt, int x, int y) {
        auto fx = fa(rt, x), fy = fa(rt, y);
        if (fx.val == fy.val) return;
        if (fx.deep > fy.deep) swap(fx, fy);
        root[rt] = tree.update(root[rt], fx.val, {fy.val, fx.deep});
        if (fx.deep == fy.deep) root[rt] = tree.update(root[rt], fy.val, {fy.val, fy.deep + 1});
    }
} dsu;