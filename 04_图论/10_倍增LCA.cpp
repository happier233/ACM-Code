const int MAX_DEP = 20;

// 倍增2^k的父亲
int fa[N][MAX_DEP];
int dep[N];

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