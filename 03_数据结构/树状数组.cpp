const int N = 50005;

struct BITree {
    int n;
    ll c[N * 2];

    void init(int n) {
        memset(c, 0, sizeof(ll) * (n + 1));
        this->n = n;
    }

    int change(int pos, ll v) {
        for (int i = pos; i <= n; i += i & (-i)) 
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