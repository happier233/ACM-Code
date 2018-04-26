#define INF 0x3f3f3f  
int lowcost[110];//此数组用来记录第j个节点到其余节点最少花费   
int map[110][110];//用来记录第i个节点到其余n-1个节点的距离   
int visit[110];//用来记录最小生成树中的节点   
int city;
int prime(){
	int min, i, j, next, mincost = 0;
	memset(visit, 0, sizeof(visit));//给最小生成树数组清零   
	for (i = 1; i <= city; i++)
	{
		lowcost[i] = map[1][i];//初始化lowcost数组为第1个节点到剩下所有节点的距离   
	}
	visit[1] = 1;//选择第一个点为最小生成树的起点   
	for (i = 1; i<city; i++)
	{
		min = INF;
		for (j = 1; j <= city; j++)
		{
			if (!visit[j] && min>lowcost[j])//如果第j个点不是最小生成树中的点并且其花费小于min   
			{
				min = lowcost[j];
				next = j;//记录下此时最小的位置节点   
			}
		}
		if (min == INF)
		{
			return INF;
		}
		mincost += min;//将最小生成树中所有权值相加   
		visit[next] = 1;//next点加入最小生成树   
		for (j = 1; j <= city; j++)
		{
			if (!visit[j] && lowcost[j]>map[next][j])//如果第j点不是最小生成树中的点并且此点处权值大于第next点到j点的权值   
			{
				lowcost[j] = map[next][j];         //更新lowcost数组   
			}
		}
	}
	return mincost;
}