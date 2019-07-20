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
        for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
            int v = gh.eg[i].e;
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
        for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
            int v = gh.eg[i].e;
            if (v == son[u] || v == fa[u]) continue;
            getpos(v, v);
        }
    }

    void build(int start, int root, int n) {
        memset(son, -1, sizeof(int) * ++n);
        tot = start; // start是线段树中的ID起始数值
        dfs(root, 0, 0);
        getpos(root, root);
    }
} treec;

// 树状数组，如果无需在线查询可以使用差分树
BITree tree;

// 点权修改
void change1(int u, int v, ll val) {
    int f1 = treec.top[u];
    int f2 = treec.top[v];
    while (f1 != f2) {
        if (treec.deep[f1] < treec.deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tree1.update(treec.p[f1], treec.p[u], val);
        u = treec.fa[f1];
        f1 = treec.top[u];
    }
    if (treec.deep[u] > treec.deep[v]) {
        swap(u, v);
    }
    tree1.update(treec.p[u], treec.p[v], val);
}

// 边权修改
void change2(int u, int v, ll val) {
    int f1 = treec.top[u];
    int f2 = treec.top[v];
    while (f1 != f2) {
        if (treec.deep[f1] < treec.deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tree2.update(treec.p[f1], treec.p[u], val);
        u = treec.fa[f1];
        f1 = treec.top[u];
    }
    if (treec.deep[u] > treec.deep[v]) {
        swap(u, v);
    }
    tree2.update(treec.p[treec.son[u]], treec.p[v], val);
}