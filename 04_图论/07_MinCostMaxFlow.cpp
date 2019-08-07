struct Edge {
    int e, nxt;
    ll flow, cost;

    Edge() {};

    Edge(int a, ll b, ll c, int d = 0) : e(a), flow(b), cost(c), nxt(d) {}
};

const ll INF = 1000000;
const int N = int(1e5 + 10);
const int M = int(1e5 + 10);

//前向星
struct Graph {
    Edge eg[M];
    int head[N];
    int cnt;

    void init(int n) {
        memset(head, -1, sizeof(int) * ++n);
        cnt = 0;
    }

    inline void addEdge(int x, int y, ll v, ll c) {
        eg[cnt] = Edge(y, v, c, head[x]);
        head[x] = cnt++;
    }
};

struct MinCostMaxFlow {
    Graph gh;
    // 点的范围[0, n)
    int n;

    // 设置N
    void init(int _n) {
        n = _n + 1;
        gh.init(n);
    }

    // 加流量，反向是负的花费
    void addFlow(int x, int y, ll f, ll c) {
        // printf("%d->%d: %lld\t%lld\n", x, y, f, c); fflush(stdout);
        gh.addEdge(x, y, f, c);
        gh.addEdge(y, x, 0, -c);
    }

    // 该pre存的是边
    int pre[N];
    int dis[N];
    bool vis[N];

    bool spfa(int s, int e) {
        queue<int> q;
        for (int i = 0; i < n; i++) {
            dis[i] = INF;
            vis[i] = false;
            pre[i] = -1;
        }
        dis[s] = 0;
        vis[s] = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
                Edge &eg = gh.eg[i];
                if (eg.flow > 0 && dis[eg.e] > dis[u] + eg.cost) {
                    dis[eg.e] = dis[u] + eg.cost;
                    pre[eg.e] = i;
                    if (!vis[eg.e]) {
                        vis[eg.e] = true;
                        q.push(eg.e);
                    }
                }
            }
        }
        return pre[e] != -1;
    }

    pll cal(int s, int e) {
        ll flow = 0, cost = 0;
        while (spfa(s, e)) {
            ll f = INF;
            for (int i = pre[e]; ~i; i = pre[gh.eg[i ^ 1].e]) {
                f = min(f, gh.eg[i].flow);
            }
            for (int i = pre[e]; ~i; i = pre[gh.eg[i ^ 1].e]) {
                gh.eg[i].flow -= f;
                gh.eg[i ^ 1].flow += f;
                cost += gh.eg[i].cost;
            }
            flow += f;
        }
        return make_pair(flow, cost);
    }

} network;

// vector图存
struct MinCostMaxFlow {
    vector<Edge> g[N];
    // 点的范围[0, n)
    int n = 0;

    // 设置N
    void init(int _n) {
        rep(i, 0, n) {
            g[i].clear();
        }
        n = _n + 1;
    }

    // 加流量，反向是负的花费
    void addFlow(int x, int y, int f, int c) {
        g[x].push_back(Edge(y, f, c, g[y].size()));
        g[y].push_back(Edge(x, 0, -c, g[x].size() - 1));
    }

    // 该pre存的是(点,边)
    pii pre[N];
    int dis[N];
    bool vis[N];
    int h[N];

    int cnt = 0;

    bool bfs(int s, int e) {
        priority_queue<pii, vector<pii>, greater<pii>> q;
        for (int i = 0; i < n; i++) {
            dis[i] = INF;
            vis[i] = false;
            pre[i] = pii(-1, -1);
        }
        dis[s] = 0;
        q.push(pii(0, s));
        while (!q.empty()) {
            pii f = q.top();
            int u = f.second;
            q.pop();
            if (f.first != dis[u]) continue;
            for (int i = 0; i < sz(g[u]); i++) {
                auto &eg = g[u][i];
                if (eg.flow == 0) continue;
                int v = eg.e;
                int cost = eg.cost + dis[u] + h[u] - h[v];
                if (dis[v] > cost) {
                    cnt++;
                    dis[v] = cost;
                    pre[v] = pii(u, i);
                    q.push(pii(dis[v], v));
                }
            }
        }
        for (int i = 0; i < n; i++) {
            h[i] += dis[i];
        }
        return pre[e].second != -1;
    }

    pii cal(int s, int e, int limit) {
        int flow = 0, cost = 0;
        memset(h, 0, sizeof(int) * n);
        cnt = 0;
        while (limit) {
            if (!bfs(s, e)) break;
            int f = INF;
            for (int i = e; ~pre[i].second; i = pre[i].first) {
                f = min(f, g[pre[i].first][pre[i].second].flow);
            }
            for (int i = e; ~pre[i].second; i = pre[i].first) {
                g[pre[i].first][pre[i].second].flow -= f;
                g[i][g[pre[i].first][pre[i].second].nxt].flow += f;
            }
            cost += f * h[e];
            flow += f;
            limit -= f;
        }
        return make_pair(flow, cost);
    }

} network;  