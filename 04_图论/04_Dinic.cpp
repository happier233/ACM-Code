#define N 2005
#define INF 0x7fffffff

struct dinic {

    struct node {
        int e;
        ll f;

        node() = default;

        node(int a, ll b) : e(a), f(b) {}
    };

    // 点的范围[0, n)
    int n;
    vector<node> eg;
    vector<int> head[N];
    // 弧优化
    int cur[N], dis[N];

    dinic() = default;

    // 设置N
    void setN(int n) {
        this->n = n;
    }

    inline void addEdge(int x, int y, ll f) {
        //printf("%d->%d: %lld\n", x, y, f);
        head[x].push_back(static_cast<int &&>(eg.size()));
        eg.push_back({y, f});
    }

    // 加流量
    void addFlow(int x, int y, ll f) {
        addEdge(x, y, f);
        addEdge(y, x, 0);
    }

    bool bfs(int s, int e) {
        fill_n(dis, n, -1);
        int q[N];
        int l, r;
        l = r = 0;
        dis[s] = 0;
        q[r++] = s;
        while (l < r) {
            int f = q[l++];
            for (const auto &i: head[f]) {
                if (eg[i].f > 0 && dis[eg[i].e] == -1) {
                    dis[eg[i].e] = dis[f] + 1;
                    q[r++] = eg[i].e;
                }
            }
        }
        return dis[e] > 0;
    }

    ll dfs(int s, int e, ll mx) {
        if (s == e || mx == 0) {
            return mx;
        }
        int flow = 0;
        for (int &k = cur[s]; k < head[s].size(); k++) {
            int &i = head[s][k];
            auto &te = eg[i];
            ll a;
            if (te.f > 0 && dis[te.e] == dis[s] + 1 && (a = dfs(te.e, e, min(te.f, mx)))) {
                te.f -= a;
                eg[i ^ 1].f += a;
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
            fill_n(cur, n, 0);
            ans += dfs(s, e, INF);
        }
        return ans;
    }

    // 清空数据
    void clear() {
        rep(i, 0, n) head[i].clear();
        eg.clear();
    }
};