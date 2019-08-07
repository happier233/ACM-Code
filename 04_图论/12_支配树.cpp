const int MAX_DEP = 20;

// 注意0,1点的边界问题
struct DominatorTree {
    int deg[N]; // 入度
    int dep[N]; //
    int dfn[N];
    int st[N];
    int tot;

    // 拓扑序, 要保证root是入度为0
    void bfs(Graph &gh, int root) {
        queue<int> q;
        q.push(root);
        tot = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            dfn[u] = ++tot;
            st[tot] = u;
            forg(i, gh.head[u], gh.eg) {
                int v = gh.eg[i].e;
                if ((--deg[v]) == 0) {
                    q.push(v);
                }
            }
        }
    }

    // 倍增2^k的父亲
    int fa[N][MAX_DEP];

    // 倍增LCA
    int lca(int u, int v) {
        if (dep[u] > dep[v]) {
            swap(u, v);
        }
        int hu = dep[u], hv = dep[v];
        int tu = u, tv = v;
        for (int det = hv - hu, i = 0; det; det >>= 1, i++) {
            if (det & 1)
                tv = fa[tv][i];
        }
        if (tu == tv) {
            return tu;
        }
        for (int i = MAX_DEP - 1; i >= 0; i--) {
            if (fa[tu][i] == fa[tv][i]) {
                continue;
            }
            tu = fa[tu][i];
            tv = fa[tv][i];
        }
        return fa[tu][0];
    }

    // 动态更新节点的父亲属性
    void lineFa(int u, int v) {
        fa[u][0] = v;
        for (int i = 1; i < MAX_DEP; i++) {
            v = fa[u][i] = fa[v][i - 1];
        }
    }

    // 建树, op是gh的反向图，用来寻找其父亲
    void build(Graph &gh, Graph &op, int n, int root) {
        memcpy(deg, gh.deg, sizeof(int) * (n + 1));
        bfs(gh, root);
        for (int k = 1; k <= tot; k++) {
            int u = st[k], fath = -1;
            dep[u] = 0;
            for (int i = op.head[u]; ~i; i = op.eg[i].nxt) {
                int v = op.eg[i].e;
                if (dfn[v] > dfn[u]) continue;
                fath = (fath == -1 ? v : lca(fath, v));
            }
            if (fath == -1) fath = u;
            lineFa(u, fath);
            dep[u] = dep[fath] + 1;
        }
    }
} dtree;