#define forg(i, h, eg) for(int i = (h); ~i; i = (eg[i]).nxt)

struct Edge {
    int e, nxt;
    ll v;
    Edge() = default;
    Edge(int a, ll b, int c = 0) : e(a), v(b), nxt(c) {}

    bool operator<(const Edge &a) const {
        return (a.v == v ? e < a.e : v < a.v);
    }
};

const ll INF = ll(1e11);
const int N = int(1e5 + 10);
const int M = int(3e5 + 10);

struct Graph {
    Edge eg[M];
    int head[N];
    int cnt;

    void init(int n) {
        memset(head, -1, sizeof(int) * ++n);
        cnt = 0;
    }

    inline void addEdge(int x, int y, ll v = 0) {
        eg[cnt] = Edge(y, v, head[x]);
        head[x] = cnt++;
    }
} gh;