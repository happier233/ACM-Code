// 巨菜的ACMer-Happy233

#include <bits/stdc++.h>

using namespace std;

//-----
typedef double db;
typedef long long ll;
typedef unsigned int ui;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second
#define pw(x) (1ll << (x))
#define bt(x, k) (((x) >> k) & 1)
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i, l, r) for(int i=(l);i<(r);++i)
#define per(i, l, r) for(int i=(r)-1;i>=(l);--i)
#define mst(t, v, n) memset(t, v, sizeof(decltype(*(t))) * (n))
#define sf(x) scanf("%d", &(x))
#ifndef ACM_LOCAL
#define endl '\n'
#endif

int main() {
#ifdef ACM_LOCAL
    freopen("./data/std.in", "r", stdin);
    // freopen("./data/std.out", "w", stdout);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#endif

#ifdef ACM_LOCAL
    auto start = clock();
#endif
    int t = 1;
//    cin >> t;
    while (t--)
        solve();
#ifdef ACM_LOCAL
    auto end = clock();
    cerr << "Run Time: " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}