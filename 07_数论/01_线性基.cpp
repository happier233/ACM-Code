#define rep(i, l, r) for(int i=(l);i<(r);++i)
#define per(i, l, r) for(int i=(r)-1;i>=(l);--i)
#define pw(x) (1ll << (x))
#define bt(x, i) ((x >> i) & 1)
const int LN = 61;
struct LB {
    ll d[LN] = {0}, p[LN] = {0};
    int g[LN] = {0};
    int cnt = 0;

    LB() = default;

    ll &operator[](int pos) {
        return d[pos];
    }

    const ll &operator[](int pos) const {
        return d[pos];
    }

    void insert(ll val, int pos) {
        per(i, 0, LN) {
            if (val & pw(i)) {
                if (!d[i]) {
                    d[i] = val;
                    g[i] = pos;
                    return;
                }
				// 贪心保留最右
                if (pos > g[i]) {
                    swap(pos, g[i]);
                    swap(val, d[i]);
                }
                val ^= d[i];
            }
        }
    }

    ll query_max(int l) {
        ll ret = 0;
        per(i, 0, LN) {
            if (g[i] >= l)
                ret = max(ret, ret ^ d[i]);
        }
        return ret;
    }

    ll query_max() {
        ll ret = 0;
        per(i, 0, LN) {
            ret = max(ret, ret ^ d[i]);
        }
        return ret;
    }

    ll query_min() {
        rep(i, 0, LN) {
            if (d[i]) return d[i];
        }
        return 0;
    }

    void rebuild() {
        per(i, 0, LN) {
            per(j, 0, i) {
                if (d[i] & (1LL << j)) d[i] ^= d[j];
            }
        }
        rep(i, 0, LN) {
            if (d[i]) p[cnt++] = d[i];
        }
    }

    ll kth_query(ll k) {
        int ret = 0;
        if (k >= pw(cnt)) return -1;
        per(i, 0, LN) {
            if (bt(k, 1)) ret ^= p[i];
        }
        return ret;
    }
};
// 求并集
LB operator+(const LB &n1, const LB &n2) {
    LB ret = n1;
    per(i, 0, LN)
        if (n2.d[i])
            ret.insert(n1.d[i], n1.g[i]);
    return ret;
}
// 求交集
LB operator^(const LB &n1, const LB &n2) {
    LB ans = {}, c = n2, d = n2;
    rep(i, 0, LN) {
        ll x = n1[i];
        if (!x) continue;
        int p = i;
        ll T = 0;
        per(j, 0, p + 1) {
            if (bt(x, j)) {
                if (c[j]) {
                    x ^= c[j];
                    T ^= d[j];
                } else {
                    p = j;
                    break;
                }
            }
        }
        if (!x) {
            ans[i] = T;
        } else {
            c[p] = x;
            d[p] = T;
        }
    }
    return ans;
}