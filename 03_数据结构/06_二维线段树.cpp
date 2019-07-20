
const int N = 1005;

struct SegTree {

    inline int son(int k, int x) {
        return (k << 2) - 2 + x;
    }

    struct node {
        int l, r;

        node() = default;

        node(int a, int b) : l(a), r(b) {}

        inline int mid() {
            return (l + r) >> 1;
        }

        inline node left() {
            return node(l, mid());
        }

        inline node right() {
            return node(mid() + 1, r);
        }

        inline bool in(int x) {
            return x >= l && x <= r;
        }

        inline bool more() {
            return l < r;
        }

        bool operator==(const node &t) {
            return l == t.l && r == t.r;
        }
    };

    ll c[N << 2][N << 2];
    ll ans[N << 4];
    ll laz[N << 4];

    inline void up(int k, bool x, bool y) {
        int s = (k << 2) - 2;
        ll t = 0;
        if (x) t += ans[s] + ans[s + 1] + laz[s] + laz[s + 1];
        if (y) t += ans[s + 2] + ans[s + 3] + laz[s + 2] + laz[s + 3];
        ans[k] = t;
    }

    inline void push(int k) {
        int s = (k << 2) - 2;
        laz[s] += laz[k];
        laz[s + 1] += laz[k];
        laz[s + 2] += laz[k];
        laz[s + 3] += laz[k];
        ans[k] += laz[k];
        laz[k] = 0;
    }

    void build(node x, node y, int k) {
        laz[k] = 0;
        if (x.more() && y.more()) {
            ans[k] = c[x.l][y.l];
            return;
        }
        ans[k] = 0;
        bool ax = false;
        bool ay = false;
        if (x.more()) {
            build(x.left(), y, son(k, 0));
            build(x.right(), y, son(k, 1));
        }
        if (y.more()) {
            build(x, y.left(), son(k, 2));
            build(x, y.right(), son(k, 3));
        }
        up(k, x.more(), y.more());
    }

    void change(node x, node y, int k, node l, node r, ll v) {
        if (x == l && y == r) {
            laz[k] += v;
            return;
        }
        push(k);
        if (x.more()) {
            if (l.r <= x.mid()) {
                change(x.left(), y, son(k, 0), l, r, v);
            } else if (l.l > x.mid()) {
                change(x.right(), y, son(k, 1), l, r, v);
            } else {
                change(x.left(), y, son(k, 0), node(l.l, x.mid()), r, v);
                change(x.right(), y, son(k, 1), node(x.mid() + 1, l.r), r, v);
            }
        }
        if (y.more()) {
            if (r.l <= y.mid()) {
                change(x, y.left(), son(k, 2), l, r, v);
            } else if (r.r > y.mid()) {
                change(x, y.right(), son(k, 3), l, r, v);
            } else {
                change(x, y.left(), son(k, 2), l, node(r.l, y.mid()), v);
                change(x, y.right(), son(k, 3), l, node(y.mid() + 1, r.r), v);
            }
        }
        up(k, x.more(), y.more());
    }

    ll query(node x, node y, int k, node l, node r) {
        if (x == l && y == r) {
            return ans[k] + laz[k];
        }
        push(k);
        ll t = 0;
        if (x.more()) {
            if (l.r <= x.mid()) {
                t += query(x.left(), y, son(k, 0), l, r);
            } else if (l.l > x.mid()) {
                t += query(x.right(), y, son(k, 1), l, r);
            } else {
                t += query(x.left(), y, son(k, 0), node(l.l, x.mid()), r);
                t += query(x.right(), y, son(k, 1), node(x.mid() + 1, l.r), r);
            }
        }
        if (y.more()) {
            if (r.l <= y.mid()) {
                t += query(x, y.left(), son(k, 2), l, r);
            } else if (r.r > y.mid()) {
                t += query(x, y.right(), son(k, 3), l, r);
            } else {
                t += query(x, y.left(), son(k, 2), l, node(r.l, y.mid()));
                t += query(x, y.right(), son(k, 3), l, node(y.mid() + 1, r.r));
            }
        }
        return t;
    }
};