#define forg(i, h, eg) for(int i = (h); ~i; i = (eg[i]).first)

struct Edge {
    int to;
    ll w;
};

inline bool operator<(Edge a, Edge b) {
    return a.w < b.w;
}

const ll INF = ll(1e11);
const int N = int(1e6 + 10);
const int M = int(2e6 + 10);

struct Graph {
    pair<int, Edge> eg[M];
    int head[N];
    int tot;

    void init(int n) {
        memset(head, -1, sizeof(int) * ++n);
        tot = 0;
    }

    inline void addEdge(int x, Edge g) {
        eg[tot] = {head[x], g};
        head[x] = tot++;
    }
    
    Edge &operator[](int p) {
        return eg[p].second;
    }
} gh;