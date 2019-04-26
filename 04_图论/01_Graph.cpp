struct node {
    int e, v, nxt;
    node() = default;
    node(int a, int b, int c = 0) : e(a), v(b), nxt(c) {}
	
    bool operator<(const node &a) const {
        return (a.v == v ? e < a.e : v < a.v);
    }
};

const ll INF = 10000000;
const int N = 100000;
const int M = 100000;

struct Graph {
    node eg[M];
    int head[N];
    int cnt;

    void init(int n) {
        memset(head, -1, sizeof(int) * ++n);
        cnt = 0;
    }
    inline void addEdge(int x, int y, int v) {
        eg[cnt] = node(y, v, head[x]);
        head[x] = cnt++;
    }
} gh;