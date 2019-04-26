const int N = 1000005;
struct BITree {
    int n;
    ll c[N];

    void init(int n) {
        memset(c, 0, sizeof(ll) * ++n);
        this->n = n;
    }

    int change(int pos, ll v) {
        for (int i = pos; i < n; i += i & (-i))
            c[i] += v;
        return 0;
    }

    ll query(int x) {
        ll ans = 0;
        for (int i = x; i > 0; i -= i & (-i))
            ans += c[i];
        return ans;
    }
};