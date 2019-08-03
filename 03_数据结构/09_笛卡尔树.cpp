// 笛卡尔树，静态建树，区间最值跳转
struct CartesianTree {
    int rt; // 根节点
    pii ch[N]; // 左右儿子
    int st[N]; // 单调栈

    void build(int n, int p[]) {
        rt = 0;
        int t = 0;
        for (int i = 1; i <= n; i++) {
            // 决定了大于还是小于
            while (t && p[st[t]] > p[i]) --t;
            if (t) { 
				// 成为上一个点的右儿子
				// 前一个点成为自己的左子节点
                ch[st[t]].second = i;
                ch[i].first = i - 1;
            } else { // 自己作为根节点
                ch[i].first = rt;
                rt = i;
            }
            st[++t] = i;
        }
    }
} dika;
