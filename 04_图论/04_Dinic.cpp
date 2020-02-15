struct Graph {
    pair<int, Edge> eg[M];
    int head[N];
    int tot;

    void init(int n) {
        memset(head, -1, sizeof(int) * ++n);
        tot = 0;
    }

    inline void addEdge(int x, Edge g) {
        eg[tot] = {head[x], g};
        head[x] = tot++;
    }
} gh;

struct Dinic {
    Graph gh;
    // 点的范围[0, n)
    int n;
    // 弧优化
    int cur[N], dis[N];

    Dinic() {};

    // 设置N
    void init(int _n) {
        n = _n + 1;
        gh.init(n);
    }

    // 加流量
    void addFlow(int x, int y, ll f) {
        printf("%d->%d: %lld\n", x, y, f);
        gh.addEdge(x, {y, f});
        gh.addEdge(y, {x, 0});
    }

    bool bfs(int s, int e) {
        memset(dis, -1, sizeof(int) * n);
        int q[N];
        int l, r;
        l = r = 0;
        dis[s] = 0;
        q[r++] = s;
        while (l < r) {
            int f = q[l++];
            for (int i = gh.head[f]; ~i; i = gh.eg[i].first) {
                auto &eg = gh.eg[i].second;
                int to = eg.to;
                if (eg.w > 0 && dis[to] == -1) {
                    dis[to] = dis[f] + 1;
                    q[r++] = to;
                }
            }
        }
        return dis[e] > 0;
    }

    ll dfs(int s, int e, ll mx) {
        if (s == e || mx == 0) {
            return mx;
        }
        ll flow = 0;
        for (int &k = cur[s]; ~k; k = gh.eg[k].first) {
            auto &eg = gh.eg[k].second;
            ll a;
            if (eg.w > 0 && dis[eg.to] == dis[s] + 1 && (a = dfs(eg.to, e, min(eg.w, mx)))) {
                eg.w -= a;
                gh.eg[k ^ 1].second.w += a;
                flow += a;
                mx -= a;
                if (mx <= 0) break;
            }
        }
        return flow;
    }

    ll max_flow(int s, int e) {
        ll ans = 0;
        while (bfs(s, e)) {
            memcpy(cur, gh.head, sizeof(int) * n);
            ans += dfs(s, e, INF);
        }
        return ans;
    }
} dinic;