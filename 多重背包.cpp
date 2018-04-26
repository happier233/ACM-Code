//多重背包(MultiplePack): 有N种物品和一个容量为V的背包。  
//第i种物品最多有n[i]件可用，每件费用是c[i]，价值是w[i]。  
//求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，  
//且价值总和最大。  
//HDU 2191  
  
#include <cstdio>  
#include <cstring>  
#define N 247  
int max(int x,int y){
    return x>y?x:y;  
}  
int main()  {  
    int t,n,m,i,j,k;  
    int w[N],pri[N],num[N],f[N];  
    while(~scanf("%d",&t)){  
        while(t--){  
            memset(f,0,sizeof(f));  
            scanf("%d%d",&n,&m);//n为总金额，m为大米种类  
            for(i = 0 ; i < m ; i++){  
                scanf("%d%d%d",&pri[i],&w[i],&num[i]);//num[i]为每种大米的袋数  
            }  
            for(i = 0 ; i < m ; i++){  
                for(k = 0 ; k < num[i] ; k++){  
                    for(j = n ; j >= pri[i]; j--){  
                        f[j] = max(f[j],f[j-pri[i]]+w[i]);  
                    }  
                }  
            }  
            printf("%d\n",f[n]);  
        }  
    }  
    return 0;  
}  