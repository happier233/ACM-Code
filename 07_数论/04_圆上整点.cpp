// x^2+y^2=r^2 --> y^2=(r-x)*(r+x)
// d = gcd(r-x,r+x), n=(r-x)/d, m=(r+x)/d, y^2=d^2*m*n
// 因为y^2和d^2为完全平方数，所以 n*m 为完全平方数
// 又因为n,m互质，所以 n=u^2, m =v^2
// 所以 r-y=d*u^2, r+y=d*v^2
// 可得 x=d*(v^2-u^2), y=d*u*v

ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }

inline int work(vector<pll> &p, ll d, ll t) { // d * t == 2 * r
    int sum = 0;
    for (ll u = 1; 2 * u * u < t; u++) {
        ll v = ll(sqrt(t - u * u));
        if (v == u || v * v + u * u != t || gcd(u, v) != 1) continue;
        ll x = d * (v * v - u * u) / 2;
        ll y = d * u * v;
        p.push_back({x, y});
        sum++;
    }
    return sum;
}

int calc(vector<pll> &p, ll r) {
    int sum = 0;
    r <<= 1;
    for (ll i = 1; i * i <= r; i++) { // sqrt 枚举因子
        if (r % i) continue;
        sum += work(p, i, r / i);
        if (i * i < r) sum += work(p, r / i, i);
    }
    for (int i = 0, cnt = p.size(); i < cnt; i++) {
        int x = p[i].fi, y = p[i].se;
        p.push_back({x, -y}), p.push_back({-x, y}), p.push_back({-x, -y});
    }
    sum <<= 2;
    r >>= 1;
    sum += 4;
    p.push_back({r, 0}), p.push_back({-r, 0}), p.push_back({0, r}), p.push_back({0, -r});
    sort(p.begin(), p.end());
    return sum;
}