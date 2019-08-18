int dis;
// linkx: x链接的y，linky: y链接的x
int linkx[N], linky[N];
int dx[N], dy[N];
bool vis[N];

bool searchP(int n) {
    queue<int> q;
    dis = INF;
    mst(dx, -1, n);
    mst(dy, -1, n);
    for (int i = 0; i < n; i++) {
        if (linkx[i] == -1) {
            q.push(i);
            dx[i] = 0;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dx[u] > dis) break;
        for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
            int v = gh.eg[i].e;
            if (dy[v] == -1) {
                dy[v] = dx[u] + 1;
                if (linky[v] == -1) {
                    dis = dy[v];
                } else {
                    dx[linky[v]] = dy[v] + 1;
                    q.push(linky[v]);
                }
            }
        }
    }
    return dis != INF;
}

bool dfs(int u) {
    for (int i = gh.head[u]; ~i; i = gh.eg[i].nxt) {
        int v = gh.eg[i].e;
        if (!vis[v] && dy[v] == dx[u] + 1) {
            vis[v] = true;
            if (linky[v] != -1 && dy[v] == dis) continue;
            if (linky[v] == -1 || dfs(linky[v])) {
                linky[v] = u;
                linkx[u] = v;
                return true;
            }
        }
    }
    return false;
}

int MaxMatch(int n) {
    int rst = 0;
    mst(linkx, -1, n);
    mst(linky, -1, n);
    while (searchP(n)) {
        mst(vis, false, n);
        for (int i = 0; i < n; i++) {
            if (linkx[i] == -1 && dfs(i)) {
                rst++;
            }
        }
    }
    return rst;
}