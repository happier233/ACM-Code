ll gcd(ll x, ll y) { // 循环版
	ll t;
	while (y){
		t = x % y;
		x = y;
		y = t;
	}
	return  x;
}

ll gcd(ll a, ll b) { // 递归版
    return b == 0 ? a : gcd(b, a % b);
}

// 扩展欧几里得
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll q = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return q;
}