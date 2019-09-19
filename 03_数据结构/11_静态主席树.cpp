// m=update count,MAXN>=m*log(n)
const int N = int(2e5 + 10);
const int MAXN = int(1e7 + 10);

struct PSegTree {
    const int *a;
    pii ran; // Tree Range
    int c[MAXN];
    int tot = 0;
    int lson[MAXN], rson[MAXN];

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

    int init(int l, int r, const int num[]) {
        tot = 0;
        a = num;
        ran = {l, r};
        return build(l, r);
    }

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

    // r1=right_root,r2=left_root,kth number
    int query(int r1, int r2, int k) {
        int l, r;
        tie(l, r) = ran;
        while (l < r) {
            int mid = (l + r) >> 1;
            int cnt = c[lson[r1]] - c[lson[r2]];
            if (cnt >= k) {
                r1 = lson[r1], r2 = lson[r2];
                r = mid;
            } else {
                k -= cnt;
                r1 = rson[r1], r2 = rson[r2];
                l = mid + 1;
            }
        }
        return l;
    }
	
	// r1=right_root,r2=left_root, sum of num<=k
    int sum(int r1, int r2, int k) {
        int l, r;
        tie(l, r) = ran;
        int ans = 0;
        while (l < r) {
            int mid = (l + r) >> 1;
            int cnt = c[lson[r1]] - c[lson[r2]];
            if (k <= mid) {
                r1 = lson[r1], r2 = lson[r2];
                r = mid;
            } else {
                ans += cnt;
                r1 = rson[r1], r2 = rson[r2];
                l = mid + 1;
            }
        }
        ans += c[r1] - c[r2];
        return ans;
    }
} tree;