#define N 105
#define M 10005
int n, m, k;
pii eg[M * 2];
int result[N * 2];
int head[N * 2];
int cnt = 0;

void addEdge(int x, int y) {
    eg[cnt].first = y;
    eg[cnt].second = head[x];
    head[x] = cnt++;
}

bool vis[M * 2] = {false};

int dfs(int x) {
    for (int i = head[x]; ~i; i = eg[i].second) {
        int y = eg[i].first;
        if (!vis[y]) {
            vis[y] = true;
            if (result[y] == -1 || dfs(result[y])) {
                result[y] = x;
                return 1;
            }
        }
    }
    return 0;
}

int MaxMatch() {
    int ans = 0;
    memset(result, -1, sizeof(result));
    rep(i, 1, n + 1) {
        memset(vis, 0, sizeof(vis));
        ans += dfs(i);
    }
    return ans;
}

void solve() {
    scanf("%d%d", &m, &k);
    memset(head, -1, sizeof(head));
    cnt = 0;
    rep(i, 0, k) {
        int x, y;
        scanf("%d%d", &x, &y);
        addEdge(x, y);
    }
    int ans = MaxMatch();
    printf("%d\n", ans);
}