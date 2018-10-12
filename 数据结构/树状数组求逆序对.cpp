BITree t;
int n;
pii a[N];

void solve() {
    t.init(n);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = make_pair(x, i);
    }
    sort(a + 1, a + n + 1);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        t.change(a[i].second, 1);
        ans += (i - t.query(a[i].second));
    }
    cout << ans << endl;
}

