// 题意: n个节点的树，存在边权，范围1e18
// 求任意两点之间点集的子集中两点之间路径异或和为0的个数
// u<v,u'<v',(u',v') ∈ path(u,v),求path(u', v')异或和==0

struct Edge {
    int to, nxt;
    ll w;
};
const int N = int(1e5 + 10);
const int M = N << 1;

struct Grahp {
    int head[N];
    Edge eg[M];
    int tot;

    void init(int n) {
        memset(head, -1, sizeof(int) * ++n);
    }

    inline void addEdge(int u, int v, ll w) {
        eg[tot] = {v, head[u], w};
        head[u] = tot++;
    }
} gh;

bool vis[N];
// q队列, fa祖先, sz是子树大小, smx是子树最大
int q[N], fa[N], sz[N], smx[N];

int froot(int s) {
    int l, r, mn = N, rt = 0;
    q[l = r = 1] = s;
    while (l <= r) {
        int u = q[l++];
        sz[u] = 1;
        smx[u] = 0;
        for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
            int v = gh.eg[i].to;
            if (v == fa[u] || vis[v]) continue;
            fa[v] = u;
            q[++r] = v;
        }
    }
    // 反向遍历所有点算size
    while (--l) {
        int u = q[l];
        int mx = max(smx[u], r - sz[u]);
        if (mx < mn) mn = mx, rt = u;
        if (l == 1) break; // 根节点没有fa
        sz[fa[u]] += sz[u];
        smx[fa[u]] = max(smx[fa[u]], sz[u]);
    }
    return rt;
}

// sons子树方向节点个数, val根到该节点异或和, gc边后继方向的节点个数
int sons[N], gc[M];
ll val[N];
ll ans = 0;
int n;

const int MOD = int(1e9 + 7);

ll nums[N];
int cnt[N];

void go(int s, int rt) {
    fa[s] = rt;
    val[s] = 0;
    int l, r;
    // 不计算s
    q[l = r = 0] = s;
    int m = 0;
    while (l <= r) {
        int u = q[l++];
        nums[m++] = val[u];
        for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
            int v = gh.eg[i].to;
            if (v == fa[u] || vis[v]) continue;
            fa[v] = u;
            q[++r] = v;
            val[v] = val[u] ^ gh.eg[i].w;
            // 这个点方向后面有多少点
            sons[v] = gc[i];
        }
    }
    sort(nums, nums + m);
    m = unique(nums, nums + m) - nums;
    mst(cnt, 0, m);
    // 遍历分支
    for (int j = gh.head[s]; ~j; j = gh.eg[j].nxt) {
        // 分支的根
        int du = gh.eg[j].to;
        if (vis[du]) continue;
        q[l = r = 1] = du;
        while (l <= r) {
            int u = q[l++];
            int k = lower_bound(nums, nums + m, val[u]) - nums;
            (ans += 1ll * sons[u] * cnt[k] % MOD) %= MOD;
            if (val[u] == 0) {
                (ans += 1ll * sons[u] * (n - gc[j]) % MOD) %= MOD;
            }
            for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
                int v = gh.eg[i].to;
                if (v == fa[u] || vis[v]) continue;
                q[++r] = v;
            }
        }
        // 增加这个方向的值
        while (--l) {
            int u = q[l];
            int k = lower_bound(nums, nums + m, val[u]) - nums;
            (cnt[k] += sons[u]) %= MOD;
        }
    }
}

void work(int u) {
    // 换根
    u = froot(u);
    vis[u] = true;
    go(u, 0);
    for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
        int v = gh.eg[i].to;
        if (vis[v]) continue;
        work(v);
    }
}

// 预处理边后继节点个数
int pdfs(int u, int f) {
    int fg_id = -1;
    int s = 1;
    for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
        int v = gh.eg[i].to;
        if (v == f) { // 记录父边ID
            fg_id = i;
            continue;
        }
        int c = pdfs(v, u);
        gc[i] = c;
        s += c;
    }
    // 存在父边
    if (~fg_id) gc[fg_id] = n - s;
    return s;
}

void solve() {
    while (cin >> n) {
        gh.init(n);
        for (int i = 2; i <= n; i++) {
            int u, v;
            ll w;
            u = i;
            cin >> v >> w;
            gh.addEdge(u, v, w);
            gh.addEdge(v, u, w);
        }
        mst(vis, false, n + 1);
        pdfs(1, 0);
        ans = 0;
        work(1);
        cout << ans << endl;
    }
}