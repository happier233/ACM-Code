/*
* Prim 求 MST
* 耗费矩阵 cost[][]，标号从 0 开始，0∼n-1
* 返回最小生成树的权值，返回 -1 表示原图不连通
 */
const int INF = 0x3f3f3f3f;
const int N = 110;
bool vis[N];
int lowc[N]; //点是 0 n-1 
int prim(int cost[][N], int n) {
    int ans = 0;
    memset(vis, false, sizeof(vis));
    vis[0] = true;
    for (int i = 1; i < n; i++)lowc[i] = cost[0][i];
    for (int i = 1; i < n; i++) {
        int minc = INF;
        int p =−1;
        19
        for (int j = 0; j < n; j++)
            if (!vis[j] && minc > lowc[j]) {
                minc = lowc[j];
                p = j;
            }
        if (minc == INF)return −1;//原图不连通 
        ans += minc;
        vis[p] = true;
        for (int j = 0; j < n; j++)
            if (!vis[j] && lowc[j] > cost[p][j])
                lowc[j] = cost[p][j];
    }
    return ans;
}