const int N = int(2e5 + 10);
// m: update count,MAXN>=m*log(n)^2
const int MAXN = int(4e7 + 10);

struct PSegTree {
    const int *a;
    pii ran;
    int n;
    int c[MAXN];
    int tot = 0;
    int lson[MAXN], rson[MAXN];
    // t: static root,s: dynamic root
    int t[N], s[N];

    int build(int l, int r) {
        int k = ++tot;
        c[k] = 0;
        if (l == r) {
            return k;
        }
        int mid = (l + r) >> 1;
        lson[k] = build(l, mid);
        rson[k] = build(mid + 1, r);
        return k;
    }

    // SegTree Range and n points, num can be nullptr
    int init(int l, int r, int _n, const int num[]) {
        tot = 0;
        a = num;
        ran = {l, r};
        n = _n;
        int rt = build(l, r);
        for (int i = 0; i <= n; i++) t[i] = s[i] = rt;
        return rt;
    }

    // build static tree
    inline void change(int id, int p, int v) {
        if (v == 0) t[id] = t[id - 1];
        else t[id] = update(t[id - 1], p, v);
    }

    // update data
    int update(int rt, int p, int v) {
        int k = ++tot, rst = k;
        int l, r;
        tie(l, r) = ran;
        // calc
        c[k] = c[rt] + v;
        while (l < r) {
            int mid = (l + r) >> 1;
            // 下面的逗号表达式顺序不能换
            if (p <= mid) {
                // go left
                rson[k] = rson[rt], rt = lson[rt], k = lson[k] = ++tot;
                r = mid;
            } else {
                // go right
                lson[k] = lson[rt], rt = rson[rt], k = rson[k] = ++tot;
                l = mid + 1;
            }
            // calc
            c[k] = c[rt] + v;
        }
        return rst;
    }

    inline void add(int id, int p, int v) {
        // BITree with PSegTree
        for (int i = id; i <= n; i += (i & -i))
            s[i] = update(s[i], p, v);
    }

    // calc lson value in use
    inline int sum(int use[], int cnt) {
        int ans = 0;
        for (int i = 0; i < cnt; i++)
            ans += c[lson[use[i]]];
        return ans;
    }

    // calc value in use
    inline int calc(int use[], int cnt) {
        int ans = 0;
        for (int i = 0; i < cnt; i++)
            ans += c[use[i]];
        return ans;
    }

    int use1[N], use2[N];

    // ans=p1-p2
    int query(int p1, int p2, int k) {
        int r1 = t[p1], r2 = t[p2];
        int cnt1 = 0, cnt2 = 0;
        // calc root in need
        for (int i = p1; i; i -= (i & -i)) use1[cnt1++] = s[i];
        for (int i = p2; i; i -= (i & -i)) use2[cnt2++] = s[i];
        int l, r;
        tie(l, r) = ran;
        int ans = 0;
        while (l < r) {
            int mid = (l + r) >> 1;
            int cnt = c[lson[r1]] - c[lson[r2]] + sum(use1, cnt1) - sum(use2, cnt2);
            if (k <= mid) {
                // go left
                r1 = lson[r1], r2 = lson[r2];
                for (int i = 0; i < cnt1; i++) use1[i] = lson[use1[i]];
                for (int i = 0; i < cnt2; i++) use2[i] = lson[use2[i]];
                r = mid;
            } else {
                // go right
                ans += cnt;
                r1 = rson[r1], r2 = rson[r2];
                for (int i = 0; i < cnt1; i++) use1[i] = rson[use1[i]];
                for (int i = 0; i < cnt2; i++) use2[i] = rson[use2[i]];
                l = mid + 1;
            }
        }
        int cnt = c[r1] - c[r2] + calc(use1, cnt1) - calc(use2, cnt2);
        ans += cnt;
        return ans;
    }
} tree;