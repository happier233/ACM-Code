// m: update count,MAXN>=m*log(n)^2
const int N = int(2e5 + 10);
const int MAXN = int(2e7 + 10);
const int MAXM = int(2e7 + 10);
const int LN = 40;

struct PSegTree {
    const int *a;
    pii ran;
    int n;
    ll c[MAXN];
    int tot = 0;
    int lson[MAXN], rson[MAXN];
    // t: static root, s: dynamic root
    int s[N], t[N];

    // SegTree Range and n points, num can be nullptr
    void init(int l, int r, int _n, const int num[]) {
        tot = 0;
        a = num;
        ran = {l, r};
        n = _n;
        for (int i = 0; i <= n; i++) s[i] = t[i] = 0;
        // init node 0
        lson[0] = rson[0] = 0;
        c[0] = 0;
    }

    inline int get(int &k, bool flag) {
        if (k == 0 || flag) {
            k = ++tot;
            lson[k] = rson[k] = 0;
        }
        return k;
    }

    // update the root in k
    void update(int k[], int rt[], int cnt, int p, int v, bool flag = false) {
        // calc
        for (int i = 0; i < cnt; i++)
            c[k[i]] = c[rt[i]] + v;
        int l, r;
        tie(l, r) = ran;
        while (l < r) {
            int mid = (l + r) >> 1;
            // 下面的逗号表达式顺序不能换
            if (p <= mid) {
                // go left
                for (int i = 0; i < cnt; i++) {
                    rson[k[i]] = rson[rt[i]];
                    rt[i] = lson[rt[i]], k[i] = get(lson[k[i]], flag);
                }
                r = mid;
            } else {
                // go right
                for (int i = 0; i < cnt; i++) {
                    lson[k[i]] = lson[rt[i]];
                    rt[i] = rson[rt[i]], k[i] = get(rson[k[i]], flag);
                }
                l = mid + 1;
            }
            // calc
            for (int i = 0; i < cnt; i++)
                c[k[i]] = c[rt[i]] + v;
        }
    }

    // build static tree
    void change(int pos, int p, int v) {
        // use int as the int[]
        // must use variable because I use the pointer
        int rt = t[pos - 1];
        int k = t[pos] = ++tot;
        update(&k, &rt, 1, p, v, true);
    }

    int use1[LN], use2[LN];

    // edit dynamic tree
    void add(int pos, int p, int v) {
        // memory reuse
        int *k = use1, *rt = use2;
        int cnt = 0;
        for (int i = pos; i <= n; i += (i & -i), cnt++) {
            rt[cnt] = s[i], k[cnt] = get(s[i], false);
        }
        update(k, rt, cnt, p, v);
    }

    // calc lson value in use
    inline ll sum(int use[], int cnt) {
        ll ans = 0;
        for (int i = 0; i < cnt; i++)
            ans += c[lson[use[i]]];
        return ans;
    }

    // calc value in use
    inline ll calc(int use[], int cnt) {
        ll ans = 0;
        for (int i = 0; i < cnt; i++)
            ans += c[use[i]];
        return ans;
    }

    // ans=p1-p2
    ll querySum(int p1, int p2, int k) {
        int rt1 = t[p1], rt2 = t[p2];
        ll cnt1 = 0, cnt2 = 0;
        // calc root in need
        for (int i = p1; i; i -= (i & -i)) use1[cnt1++] = s[i];
        for (int i = p2; i; i -= (i & -i)) use2[cnt2++] = s[i];
        int l, r;
        tie(l, r) = ran;
        ll ans = 0;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (k <= mid) {
                // go left
                rt1 = lson[rt1], rt2 = lson[rt2];
                for (int i = 0; i < cnt1; i++) use1[i] = lson[use1[i]];
                for (int i = 0; i < cnt2; i++) use2[i] = lson[use2[i]];
                r = mid;
            } else {
                // go right
                ll cnt = sum(use1, cnt1) - sum(use2, cnt2) + c[lson[rt1]] - c[lson[rt2]];
                ans += cnt;
                rt1 = rson[rt1], rt2 = rson[rt2];
                for (int i = 0; i < cnt1; i++) use1[i] = rson[use1[i]];
                for (int i = 0; i < cnt2; i++) use2[i] = rson[use2[i]];
                l = mid + 1;
            }
        }
        ll cnt = calc(use1, cnt1) - calc(use2, cnt2) + c[rt1] - c[rt2];
        ans += cnt;
        return ans;
    }

    // query k
    int queryK(int p1, int p2, int k) {
        int r1 = t[p1], r2 = t[p2];
        int cnt1 = 0, cnt2 = 0;
        // calc root in need
        for (int i = p1; i; i -= (i & -i)) use1[cnt1++] = s[i];
        for (int i = p2; i; i -= (i & -i)) use2[cnt2++] = s[i];
        int l, r;
        tie(l, r) = ran;
        while (l < r) {
            int mid = (l + r) >> 1;
            int cnt = c[lson[r1]] - c[lson[r2]] + sum(use1, cnt1) - sum(use2, cnt2);
            if (cnt >= k) {
                // go left
                r1 = lson[r1], r2 = lson[r2];
                for (int i = 0; i < cnt1; i++) use1[i] = lson[use1[i]];
                for (int i = 0; i < cnt2; i++) use2[i] = lson[use2[i]];
                r = mid;
            } else {
                // go right
                k -= cnt;
                r1 = rson[r1], r2 = rson[r2];
                for (int i = 0; i < cnt1; i++) use1[i] = rson[use1[i]];
                for (int i = 0; i < cnt2; i++) use2[i] = rson[use2[i]];
                l = mid + 1;
            }
        }
        return l;
    }
} tree;