struct Maze01 {
    // 原始01矩阵 1-n 1-m
    bool a[N][N];
    // 以(i,j)向上最大高度的最大子矩阵的左右高
    int l[N][N], r[N][N], h[N][N];
    // 最大连续前缀1的左端位置, 如果(i,j)为0则ml=j+1
    int ml[N][N];
    // 矩阵大小
    int n, m;

    void prework() {
        for (int i = 1; i <= m; i++) {
            l[0][i] = 0;
            r[0][i] = m;
        }
        for (int i = 1; i <= n; i++) {
            int maxl = 1;
            int maxr = m;
            for (int j = 1; j <= m; j++) {
                if (a[i][j] == 0) {
                    maxl = j + 1;
                    h[i][j] = l[i][j] = 0;
                } else {
                    h[i][j] = h[i - 1][j] + 1;
                    l[i][j] = max(maxl, l[i - 1][j]);
                }
                ml[i - 1][j] = maxl;
                ml[i][j] = j + 1;
            }
            for (int j = m; j >= 1; --j) {
                if (a[i][j] == 0) {
                    maxr = j - 1;
                    r[i][j] = m;
                } else {
                    r[i][j] = min(maxr, r[i - 1][j]);
                }
            }
        }
    }

    // 单调栈
    pii st[N];

    int calc() {
        prework();
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int top = 0;
            for (int j = 1; j <= m; j++) {
                if (h[i][j] == 0) continue;
                if (top == 0 || st[top] != make_pair(l[i][j], r[i][j])) {
                    st[++top] = make_pair(l[i][j], r[i][j]);
                }
                while (top && st[top].second == j) {
                    int pos = st[top--].first;
                    if (pos < ml[i][j]) {
                        // l[i][j]-r[i][j]为底, h[i][j]为高
                        // 可以得到所有的唯一子矩阵, 不存在maze1完全属于maze2
                        ans++;
                    }
                }
            }
        }
        return ans;
    }
} dp;