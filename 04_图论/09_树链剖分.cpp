struct TreeChain {
    int top[N]; // 链条顶端点ID
    int fa[N]; // 父亲节点
    int son[N]; // 重儿子
    int deep[N]; // 深度
    int num[N]; // 儿子节点数（包括自己）

    int p[N]; // 在线段树中的ID，
    int fp[N]; // 线段树中ID对应的点
    int tot;

    void dfs(int u, int pre, int d) {
        num[u] = 1;
        deep[u] = d;
        fa[u] = pre;
        son[u] = -1;
        for (int i = gh.head[u]; ~i; i = gh.eg[i].first) {
            int v = gh.eg[i].second.to;
            if (v == pre) continue;
            dfs(v, u, d + 1);
            num[u] += num[v];
            if (son[u] == -1 || num[v] > num[son[u]]) {
                son[u] = v;
            }
        }
    }

    void getpos(int u, int sp) {
        top[u] = sp;
        p[u] = tot++;
        fp[p[u]] = u;
        if (son[u] == -1) return;
        getpos(son[u], sp);
        for (int i = gh.head[u]; ~i; i = gh.eg[i].first) {
            int v = gh.eg[i].second.to;
            if (v == son[u] || v == fa[u]) continue;
            getpos(v, v);
        }
    }
    
    // start是线段树中的ID起始数值
    void build(int n, int root = 1, int start = 1) {
        tot = start;
        // deep起始值如果是0，则遇到数据错误超出这棵树，有可能死循环
        // dfs(root, 0, 0);
        dfs(root, 0, 1);
        getpos(root, root);
    }

    int lca(int u, int v) {
        int f1 = top[u];
        int f2 = top[v];
        while (f1 != f2) {
            if (deep[f1] < deep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            u = fa[f1];
            f1 = top[u];
        }
        return deep[u] < deep[v] ? u : v;
    }
} tch;

// 树状数组，如果无需在线查询可以使用差分树
BITree tree;

// 点权修改
void change1(int u, int v, ll val) {
    int f1 = tch.top[u];
    int f2 = tch.top[v];
    while (f1 != f2) {
        if (tch.deep[f1] < tch.deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tree1.update(tch.p[f1], tch.p[u], val);
        u = tch.fa[f1];
        f1 = tch.top[u];
    }
    if (tch.deep[u] > tch.deep[v]) {
        swap(u, v);
    }
    tree1.update(tch.p[u], tch.p[v], val);
}

// 边权修改
void change2(int u, int v, ll val) {
    int f1 = tch.top[u];
    int f2 = tch.top[v];
    while (f1 != f2) {
        if (tch.deep[f1] < tch.deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tree2.update(tch.p[f1], tch.p[u], val);
        u = tch.fa[f1];
        f1 = tch.top[u];
    }
    if (tch.deep[u] > tch.deep[v]) {
        swap(u, v);
    }
    tree2.update(tch.p[tch.son[u]], tch.p[v], val);
}