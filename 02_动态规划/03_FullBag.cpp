/* 
完全背包问题的特点是，每种物品可以无限制的重复使用，可以选择放或不放。 
完全背包问题描述： 
有N物品和一个容量为V的背包。第i件物品的重量是wei[i]，价值是val[i]。 
*/  
  
#include <cstdio>  
#define INF 0x3fffffff  
#define N 10047  
int f[N],val[N],wei[N];  
int min(int a,int b)  
{  
    return x<y?x:y;  
}  
int main()  
{  
    int t,i,j,k,E,F,m,n;  
    scanf("%d",&t);  
    while(t--)  
    {  
        scanf("%d%d",&E,&F);  
        int c = F-E;  
        for(i = 0 ; i <= c ; i++)  
            f[i]=INF;  
        scanf("%d",&n);  
        for(i = 0 ; i < n ; i++)  
        {  
            scanf("%d%d",&val[i],&wei[i]);//val[i]为面额，wei[i]为重量  
        }  
        f[0]=0;//因为此处假设的是小猪储钱罐 恰好装满 的情况  
        //注意初始化（要求恰好装满背包，那么在初始化时除了f[0]为0其它f[1..V]均设为-∞，  
        //这样就可以保证最终得到的f[N]是一种恰好装满背包的最优解。  
        //如果并没有要求必须把背包装满，而是只希望价格尽量大，初始化时应该将f[0..V]全部设为0）  
        for(i =0 ; i < n ; i++)  
        {  
            for(j = wei[i] ; j <= c ; j++)  
            {  
                f[j] = min(f[j],f[j-wei[i]]+val[i]);//此处求的是最坏的情况所以用min，确定最少的钱,当然最后就用max了，HEHE  
            }  
        }  
        if(f[c] == INF)  
            printf("This is impossible.\n");  
        else  
            printf("The minimum amount of money in the piggy-bank is %d.\n",f[c]);  
    }  
    return 0;  
}  
//此代码为HDU1114;  