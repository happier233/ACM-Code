bool vis[N];
int q[N], fa[N], sz[N];

int froot(int s) {
    int l, r, mn = N, rt = 0;
    q[l = r = 1] = s;
    for (; l <= r; l++) {
        int u = q[l];
        for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
            int v = gh.eg[i].to;
            if (v == fa[u] || vis[v]) continue;
            fa[v] = u;
            q[++r] = v;
        }
    }
    // 反向遍历所有点算size
    while (--l) {
        int u = q[l], mx = 0;
        sz[u] = 1;
        for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
            int v = gh.eg[i].to;
            if (v == fa[u] || vis[v]) continue;
            mx = max(mx, sz[v]);
            sz[u] += sz[v];
        }
        mx = max(mx, r - sz[u]);
        if (mx < mn) mn = mx, rt = u;
    }
    return rt;
}

int dis[N];
ll ans[3] = {0};
const int MOD = int(1e9 + 7);

void go(int s, int rt) {
    fa[s] = rt;
    dis[s] = 0;
    pll a[3] = {};
    for (int j = gh.head[s]; ~j; j = gh.eg[j].nxt) {
        int du = gh.eg[j].to;
        if (vis[du]) continue;
        fa[du] = s;
        dis[du] = gh.eg[j].val;
        int l, r;
        q[l = r = 1] = du;
        pll b[3] = {};
        for (; l <= r; l++) {
            int u = q[l];
            b[dis[u] % 3].first += dis[u];
            b[dis[u] % 3].second++;
            for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
                int v = gh.eg[i].to;
                if (v == fa[u] || vis[v]) continue;
                fa[v] = u;
                q[++r] = v;
                dis[v] = dis[u] + gh.eg[i].val;
            }
        }
        rep(x, 0, 3) {
            ans[x] += b[x].first;
            rep(y, 0, 3) {
                (ans[(x + y) % 3] += (a[x].first * b[y].second + b[y].first * a[x].second) % MOD) %= MOD;
            }
        }
        rep(x, 0, 3) {
            a[x].first += b[x].first;
            a[x].second += b[x].second;
        }
    }
    return;
}

void dfs(int u) {
    // 换根
    u = froot(u);
    vis[u] = true;
    go(u, 0);
    for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
        int v = gh.eg[i].to;
        if (vis[v]) continue;
        dfs(v);
    }
}