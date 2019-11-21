/*
DSU On Tree 树上启发式合并
进行轻重链剖分，每次先递归轻链，然后消除轻儿子影响，然后计算重儿子，并且保留重儿子结果
然后以常数级别复杂度将重儿子状态修改成当前节点状态！！！（<------重点）
然后递归计算当前子树结果
复杂度O(nlogn)*O(计算/更新)

[CF741D]一棵有根树，边上有字母a~v，求每个子树中最长的边，满足这个边上的所有字母重排后可以构成回文。
很容易想到点分治，但由于是有根树，所以点分治是做不了的。
先对没给点记录xn[x]表示x到根的路径的各个字母出现奇偶性，然后b[S]记录满足xn[x]=S的所有点x的最大深度。
类似点分治，一棵子树一棵子树地处理，每次先对子树内每个点查找之前子树中是否有能与它拼成回文串的点与它的最大深度，再更新b[]。
注意查找和更新不能同时进行，要整棵子树都查询完毕之后再进行更新操作。注意查找与更新当前子树的根。
我试图去写了一个一次进出完整查询和更新的代码，逻辑是先查询后进入最后更新，但没有合适的写法，难度太大
 */

const int N = 500005;
const int M = N << 1;
struct Edge {
    int to, next;
};

struct Gragh {
    int head[N];
    Edge eg[M];
    int tot;

    void init(int n) {
        tot = 0;
        memset(head, -1, sizeof(int) * ++n);
    }

    inline void addEdge(int u, int v) {
        eg[tot] = {v, head[u]};
        head[u] = tot++;
    }
} gh;

int tsz[N], son[N], cson;
int dep[N] = {0};

void pdfs(int u, int f) {
    dep[u] = dep[f] + 1;
    tsz[u] = 1;
    son[u] = -1;
    for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
        int v = gh.eg[i].to;
        if (v == f) continue;
        pdfs(v, u);
        tsz[u] += tsz[v];
        if (son[u] == -1 || tsz[v] > tsz[son[u]]) son[u] = v;
    }
}

bool ans[N];
char s[N];
int p[N];

void calc(int u, int f, int d) {
    p[dep[u]] ^= (1 << (s[u] - 'a'));
    for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
        int v = gh.eg[i].to;
        if (v == f || v == cson) continue;
        calc(v, u, d);
    }
}

void dfs(int u, int f, int d) {
    // 遍历轻儿子，结果删除
    for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
        int v = gh.eg[i].to;
        if (v == f || v == son[u]) continue;
        dfs(v, u, 0);
    }
    if (~son[u]) { // 计算重儿子，结果保留
        dfs(son[u], u, 1);
        cson = son[u];
    }
    calc(u, f, 1);
    cson = -1;
    for (int i = qry.head[u]; ~i; i = qry.eg[i].next) {
        int h = qry.eg[i].to;
        ans[i] = __builtin_popcount(p[h]) <= 1;
    }
    if (d == 0) { // 删除当前子树结果
        calc(u, f, -1);
    }
}

void solve() {
    int n, m;
    while (cin >> n >> m) {
        gh.init(n);
        qry.init(n);
        for (int i = 2; i <= n; i++) {
            int u;
            cin >> u;
            gh.addEdge(u, i);
        }
        s[0] = ' ';
        cin >> (s + 1);
        rep(i, 0, m) {
            int v, h;
            cin >> v >> h;
            qry.addEdge(v, h);
        }
        pdfs(1, 0);
        dfs(1, 0, 0);
        rep(i, 0, m) {
            cout << (ans[i] ? "Yes" : "No") << endl;
        }
    }
}

const int N = 500005;
const int M = N << 1;
struct Edge {
    int to, next;
};

struct Gragh {
    int head[N];
    Edge eg[M];
    int tot;

    void init(int n) {
        tot = 0;
        memset(head, -1, sizeof(int) * ++n);
    }

    inline void addEdge(int u, int v) {
        eg[tot] = {v, head[u]};
        head[u] = tot++;
    }
} gh, qry;

int tsz[N], son[N], dep[N] = {0}, fa[N], cson;
int xn[N];
int a[N];

void pdfs(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    tsz[u] = 1;
    son[u] = -1;

    xn[u] = xn[f] ^ a[u];
    for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
        int v = gh.eg[i].to;
        if (v == f) continue;
        pdfs(v, u);
        tsz[u] += tsz[v];
        if (son[u] == -1 || tsz[v] > tsz[son[u]]) son[u] = v;
    }
}


int b[1 << 22];
int rst, ans[N], mx, root;
int num[N], tot = 0;

void check(int u) {
    int bs = xn[u];
    if (b[bs]) {
        rst = max(rst, dep[u] + b[bs] - dep[root] * 2);
    }
    for (int i = 0; i < 22; i++) {
        int bt = bs ^(1 << i);
        if (b[bt]) {
            rst = max(rst, dep[u] + b[bt] - dep[root] * 2);
        }
    }
    bs ^= xn[root];
    if (bs == (bs & (-bs))) {
        rst = max(rst, dep[u] - dep[root]);
    }
}

void calc(int u) {
    check(u);
    for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
        int v = gh.eg[i].to;
        if (v == fa[u]) continue;
        calc(v);
    }
}

void add(int u) {
    if (b[xn[u]]) {
        b[xn[u]] = max(b[xn[u]], dep[u]);
    } else {
        b[xn[u]] = dep[u];
        num[tot++] = xn[u];
    }
    if (u == cson) return;
    for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
        int v = gh.eg[i].to;
        if (v == fa[u]) continue;
        add(v);
    }
}

void go(int u) {
    rst = 0;
    if (~son[u]) {
        rst = 1;
        root = son[u];
        check(son[u]);
        add(son[u]);
    }
    root = u;
    check(u);
    for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
        int v = gh.eg[i].to;
        if (v == fa[u] || v == cson) continue;
        calc(v);
        add(v);
    }
}

void del() {
    for (int i = 0; i < tot; b[num[i++]] = 0);
    tot = 0;
}

void dfs(int u, int d) {
    // 遍历轻儿子，结果删除
    for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
        int v = gh.eg[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs(v, 0);
    }
    if (~son[u]) { // 计算重儿子，结果保留
        dfs(son[u], 1);
        cson = son[u];
    }
    go(u); // 计算当前
    cson = -1;
    ans[u] = rst;
    if (d == 0) {
        del();
    }
}

void dfs2(int u) {
    for (int i = gh.head[u]; ~i; i = gh.eg[i].next) {
        int v = gh.eg[i].to;
        dfs2(v);
        ans[u] = max(ans[u], ans[v]);
    }
}

void input(int n) {
    a[1] = 0;
    for (int i = 2; i <= n; i++) {
        int f;
        char c;
        cin >> f >> c;
        gh.addEdge(f, i);
        a[i] = 1 << (c - 'a');
    }
}

void solve() {
    int n;
    while (cin >> n) {
        gh.init(n);
        input(n);
        memset(b, 0, sizeof(b));
        pdfs(1, 0);
        dfs(1, 0);
        dfs2(1);
        for (int i = 1; i <= n; i++) {
            printf("%d%c", ans[i], " \n"[i == n]);
        }
    }
}