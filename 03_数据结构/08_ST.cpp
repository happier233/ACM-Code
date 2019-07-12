struct ST {
    int ck[N];
    int rmq[N];
    int dp[20][N];

    void init(int n, int squ[]) {
        ck[0] = -1;
        for (int i = 1; i <= n; i++) {
            ck[i] = ck[i - 1] + ((i & (i - 1)) == 0 ? 1 : 0);
        }
        memcpy(rmq, squ, sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            dp[0][i] = i;
        }
        for (int k = 1; k <= ck[k]; k++) {
            int dk = k - 1;
            for (int i = 0; i < n; i++) {
                int a = dp[dk][i];
                int b = dp[dk][i + (1 << dk)];
                dp[k][i] = rmq[a] < rmq[b] ? a : b;
            }
        }
    }

    int query(int l, int r) {
        if (l > r) swap(l, r);
        int k = ck[r - l + 1];
        int a = dp[k][l];
        int b = dp[k][r - (1 << k) + 1];
        return rmq[a] < rmq[b] ? a : b;
    }
};