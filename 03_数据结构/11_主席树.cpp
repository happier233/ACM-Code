struct SegTree {
    int num[N];
    int c[M];
    ll s[M];
    pii ran;
    int tot = 0;
    int lson[M], rson[M];

    int build(int l, int r) {
        int k = ++tot;
        s[k] = c[k] = 0;
        if (l == r) {
            return k;
        }
        int mid = (l + r) >> 1;
        lson[k] = build(l, mid);
        rson[k] = build(mid + 1, r);
        return k;
    }

    int init(int l, int r) {
        ran = pii(l, r);
        tot = 0;
        return build(l, r);
    }

    int update(int rt, int p) {
        int val = num[p];
        int l, r;
        tie(l, r) = ran;
        int k = ++tot;
        int tmp = k;
        c[k] = c[rt] + 1, s[k] = s[rt] + val;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (p <= mid) {
                lson[k] = ++tot;
                rson[k] = rson[rt];
                k = lson[k], rt = lson[rt];
                r = mid;
            } else {
                lson[k] = lson[rt];
                rson[k] = ++tot;
                k = rson[k], rt = rson[rt];
                l = mid + 1;
            }
            c[k] = c[rt] + 1, s[k] = s[rt] + val;
        }
        return tmp;
    }

    pll query(int a, int b, int h) {
        int l, r;
        tie(l, r) = ran;
        int cs = c[a] - c[b];
        int cnt = 0;
        ll sum = 0;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (h <= mid) {
                a = lson[a], b = lson[b];
                r = mid;
            } else {
                cnt += c[lson[a]] - c[lson[b]];
                sum += s[lson[a]] - s[lson[b]];
                a = rson[a], b = rson[b];
                l = mid + 1;
            }
        }
        cs -= cnt;
        sum += cs * num[l];
        return pll(sum, cs);
    }
} tree;