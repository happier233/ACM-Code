#define INF 0x3f3f3f
int lowcost[110];//此数组用来记录第j个节点到其余节点最少花费
int map[110][110];//用来记录第i个节点到其余n-1个节点的距离
int visit[110];//用来记录最小生成树中的节点
int city;

int prim() {
    int min, i, j, next, mincost = 0;
    memset(visit, 0, sizeof(visit));
    for (i = 1; i <= city; i++) lowcost[i] = map[1][i];
    visit[1] = 1;
    for (i = 1; i < city; i++) {
        min = INF;
        for (j = 1; j <= city; j++) {
            if (!visit[j] && min > lowcost[j]) {
                min = lowcost[j];
                next = j;
            }
        }
        if (min == INF) return INF;
        mincost += min;
        visit[next] = 1;
        for (j = 1; j <= city; j++) {
            if (!visit[j] && lowcost[j] > map[next][j])
                lowcost[j] = map[next][j];
        }
    }
    return mincost;
}
