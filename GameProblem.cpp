// 巴什博奕, 是否先手必胜
inline bool bash_game(int n, int m){
	//一堆东西, n个物品,最多选m个
	return n % (m + 1);
}
// 威佐夫博弈, 是否先手必胜
// 有两堆各若干的物品，两人轮流从其中一堆取至少一件物品，至多不限，或从两堆中同时取相同件物品，规定最后取完者胜利。
inline bool wythoff_game(int n, int m){
	if(n > m){
		int t = n;
		n = m;
		m = t;
	}
	int temp = floor((n2-n1)*(1+sqrt(5.0))/2.0);
	return temp != n1;
}
// SG函数
#define N 1001
//f[]：可以取走的石子个数
//sg[]:0~n的SG函数值
//hash[]:mex{}
int f[N],sg[N],hash[N];
void getSG(int n)
{
    int i,j;
    memset(sg,0,sizeof(sg));
    for(i=1;i<=n;i++)
    {
        memset(hash,0,sizeof(hash));
        for(j=1;f[j]<=i;j++)
            hash[sg[i-f[j]]]=1;
        for(j=0;j<=n;j++)    //求mes{}中未出现的最小的非负整数
        {
            if(hash[j]==0)
            {
                sg[i]=j;
                break;
            }
        }
    }
}
