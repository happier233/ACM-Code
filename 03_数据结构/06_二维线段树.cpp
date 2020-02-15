const int N = int(2e3 + 48);
 
ll p[N][N];
 
struct SegTree {
 
    inline int static get(int l, int r) {
        return (l + r) | (l != r);
    }
 
    struct node {
        int l, r;
 
        inline int mid() { return (l + r) >> 1; }
 
        inline bool point() { return l == r; }
 
        inline node operator--(int) { return {l, mid()}; }
 
        inline node operator++(int) { return {mid() + 1, r}; }
 
        bool operator==(node t) const { return l == t.l && r == t.r; }
 
        operator int() { return get(l, r); }
    };
 
    ll s[N * 2][N * 2];
 
    inline void upX(node x, node y) {
        s[x][y] = max(s[x--][y], s[x++][y]);
    }
 
    inline void upY(node x, node y) {
        s[x][y] = max(s[x][y--], s[x][y++]);
    }
 
    void buildY(node x, node y) {
        if (y.point()) {
            s[x][y] = p[x.l][y.l];
            return;
        }
        buildY(x, y--);
        buildY(x, y++);
        upY(x, y);
        return;
    }
 
    void mergeY(node x, node y) {
        if (y.point()) {
            upX(x, y);
            return;
        }
        mergeY(x, y--);
        mergeY(x, y++);
        upX(x, y);
        return;
    }
 
    void build(node x, node y) {
        if (x.point()) {
            buildY(x, y);
            return;
        }
        build(x--, y);
        build(x++, y);
        mergeY(x, y);
        return;
    }
 
    ll queryY(node x, node y, node a, node b) {
        if (y == b) {
            return s[x][y];
        }
        int mid = y.mid();
        if (b.r <= mid) {
            return queryY(x, y--, a, b);
        } else if (b.l > mid) {
            return queryY(x, y++, a, b);
        } else {
            return max(queryY(x, y--, a, {b.l, mid}),
                       queryY(x, y++, a, {mid + 1, b.r}));
        }
    }
 
    ll query(node x, node y, node a, node b) {
        if (x == a) {
            return queryY(x, y, a, b);
        }
        int mid = x.mid();
        if (a.r <= mid) {
            return query(x--, y, a, b);
        } else if (a.l > mid) {
            return query(x++, y, a, b);
        } else {
            return max(query(x--, y, {a.l, mid}, b),
                       query(x++, y, {mid + 1, a.r}, b));
        }
    }
} tree;