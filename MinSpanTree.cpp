#define INF 1000000
#define N 100000
ll lowcost[N];//此数组用来记录第j个节点到其余节点最少花费
ll mpp[N][N];//用来记录第i个节点到其余n-1个节点的距离
int vis[N];//用来记录最小生成树中的节点
ll city;

ll prim() {
    ll min, i, j, next = 0, mincost = 0;
    memset(vis, 0, sizeof(vis));//给最小生成树数组清零
    for (i = 1; i <= city; i++) {
        lowcost[i] = mpp[1][i];//初始化lowcost数组为第1个节点到剩下所有节点的距离
    }
    vis[1] = 1;//选择第一个点为最小生成树的起点
    for (i = 1; i < city; i++) {
        min = INF;
        for (j = 1; j <= city; j++) {
            if (!vis[j] && min > lowcost[j])//如果第j个点不是最小生成树中的点并且其花费小于min
            {
                min = lowcost[j];
                next = j;//记录下此时最小的位置节点
            }
        }
        if (min == INF) {
            return INF;
        }
        mincost += min;//将最小生成树中所有权值相加
        vis[next] = 1;//next点加入最小生成树
        for (j = 1; j <= city; j++) {
            if (!vis[j] && lowcost[j] > mpp[next][j])//如果第j点不是最小生成树中的点并且此点处权值大于第next点到j点的权值
            {
                lowcost[j] = mpp[next][j];         //更新lowcost数组
            }
        }
    }
    return mincost;
}