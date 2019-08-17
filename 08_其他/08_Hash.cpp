struct Hash {
    int num[N];
    int tot;

    void init() { tot = 0; }

    void insert(int x) { num[tot++] = x; }

    void build() {
        sort(num, num + tot);
        tot = unique(num, num + tot) - num;
    }

    inline int operator[](int x) { return lower_bound(num, num + tot, x) - num; }
} hs;