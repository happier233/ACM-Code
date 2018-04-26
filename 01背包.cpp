/* 
01背包问题 
01背包问题的特点是，">每种物品仅有一件，可以选择放或不放。 
01背包问题描述： 
有N件物品和一个容量为V的背包。第i件物品的重量是c[i]，价值是w[i]。 
求解将哪些物品装入背包可使这些物品的重量总和不超过背包容量，且价值总和最大。 
*/  
#include <stdio.h>  
#define N 1050017  
int max(int x,int y){
    return x>y?x:y;  
}  
int wei[N],val[N],f[N];  
int main()  {  
    int i, j, n, m;  
    while(scanf("%d",&n)!=EOF){  
        scanf("%d", &m);  
        for(i=0; i<n; i++)  
            scanf("%d%d", &wei[i],&val[i]);//wei[i]为重量，val[i]为价值  
        for(i=0; i<n; i++){  
            for(j=m; j>=wei[i]; j--)  
                f[j] = max(f[j], f[j-wei[i]]+val[i]);  
        }  
        printf("%d\n",f[m]);  
    }  
    return 0;  
}  
  
//此代码为poj3624  