struct ISAP {
    Graph gh;
    // 点的范围[0, n)
    int n;
    // 弧优化
    int cur[N], dis[N];
    ISAP() {};
    // 设置N
    void init(int _n) {
        n = _n;
        gh.init(n);
    }

    // 加流量
    inline void addFlow(int x, int y, ll f) {
        gh.addEdge(x, y, f);
        gh.addEdge(y, x, 0);
    }

    int dep[N]; // 记录距离标号
    int gap[N]; // gap常数优化
    int q[N]; // 数组模拟队列

    void bfs(int s, int e) {
        memset(dep, -1, sizeof(int) * n);
        memset(gap, 0, sizeof(int) * n);
        gap[0] = 1;
        dep[e] = 0;
        int l = 0, r = 0;
        q[r++] = e;
        while (l < r) {
            int u = q[l++];
            for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
                int v = gh.eg[i].e;
                if (~dep[v]) continue;
                q[r++] = v;
                dep[v] = dep[u] + 1;
                gap[dep[v]]++;
            }
        }
    }

    ll st[N]; // 栈优化

    ll max_flow(int s, int e) {
        bfs(s, e);
        memcpy(cur, gh.head, sizeof(int) * n);
        int top = 0;
        int u = s;
        ll ans = 0;
        while (dep[s] < N) {
            if (u == e) {
                ll mf = INF;
                int sel = 0;
                for (int i = 0; i < top; i++) {
                    if (mf > gh.eg[st[i]].v) {
                        mf = gh.eg[st[i]].v;
                        sel = i;
                    }
                }

                for (int i = 0; i < top; i++) {
                    gh.eg[st[i]].v -= mf;
                    gh.eg[st[i] ^ 1].v += mf;
                }
                ans += mf;
                top = sel;
                u = gh.eg[st[top] ^ 1].e;
                continue;
            }
            bool flag = false;
            int v = 0;
            for (int i = cur[u]; ~i; i = gh.eg[i].nxt) {
                v = gh.eg[i].e;
                if (gh.eg[i].v > 0 && dep[v] + 1 == dep[u]) {
                    flag = true;
                    cur[u] = i;
                    break;
                }
            }
            if (flag) {
                st[top++] = cur[u];
                u = v;
                continue;
            }
            int mind = N;
            for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
                if (gh.eg[i].v > 0 && dep[gh.eg[i].e] < mind) {
                    mind = dep[gh.eg[i].e];
                    cur[u] = i;
                }
            }
            gap[dep[u]]--; // 当前层无法连通，降层
            if (!gap[dep[u]]) return ans; // 断层结束运算
            dep[u] = mind + 1; // 进入更高层
            gap[dep[u]]++;
            if (u != s)  u = gh.eg[st[--top] ^ 1].e;
        }
        return ans;
    }
} isap;