/*
[CF570D]一棵树，询问某棵子树指定深度(对于树根的深度)的点能否构成回文。
用二进制记录每个深度的每个字母出现次数的奇偶性即可。
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
} gh, qry;

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