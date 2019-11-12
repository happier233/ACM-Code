int dfn[N], low[N], st[N], belong[N], num[N];
bool inst[N];
int idx, top, scc;

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    st[top++] = u;
    inst[u] = true;
    for (int i = gh.head[u]; i != -1; i = gh.eg[i].nxt) {
        int v = gh.eg[i].e;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inst[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    int v;
    if (dfn[u] == low[u]) {
        scc++;
        do {
            v = st[--top];
            inst[v] = false;
            belong[v] = scc;
            num[scc]++;
        } while (u != v);
    }
}

void work() {
    fill_n(dfn, n + 1, 0);
    fill_n(num, n + 1, 0);
    fill_n(inst, n + 1, false);
    idx = top = scc = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i);
    }
}