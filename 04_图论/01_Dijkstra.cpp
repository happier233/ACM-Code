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

int dist[N];
int path[N];

void bfs(int s, int n) {
    n++;
    rep(i, 0, n) dist[i] = INF;
    memset(path, -1, sizeof(int) * n);
    dist[s] = 0;
    path[s] = s;
    priority_queue<node> q;
    q.push(node(s, dist[s]));
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        for (int i = gh.head[f.e]; ~i; i = gh.eg[i].nxt) {
            node &t = gh.eg[i];
            if (dist[t.e] > f.v + t.v) {
                dist[t.e] = f.v + t.v;
                path[t.e] = f.e;
                q.push(node(t.e, dist[t.e]));
            }
        }
    }
}

#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
typedef __gnu_pbds::priority_queue<node, greater<node>> heap;

heap::point_iterator its[N];
int cnt[N];

void dfs(int s, int n) {
    n++;
    rep(i, 0, n) dist[i] = INF;
    memset(cnt, 0, sizeof(int) * n);
    dist[s] = 0;
    cnt[s] = 1;
    heap q;
    its[s] = q.push(node(s, dist[s]));
    while (!q.empty()) {
        node f = q.top();
        q.pop();
        for (int i = gh.head[f.e]; ~i; i = gh.eg[i].nxt) {
            node &t = gh.eg[i];
            its[t.e] = 0;
            int v = f.v + t.v;
            if (dist[t.e] > v) {
                dist[t.e] = v;
                if (its[t.e] != 0) {
                    q.modify(its[t.e], node(t.e, dist[t.e]));
                } else {
                    its[t.e] = q.push(node(t.e, dist[t.e]));
                }
                cnt[t.e] = cnt[f.e];
            } else if (dist[t.e] == v) {
                (cnt[t.e] += cnt[f.e]) %= 100003;
            }
        }
    }
}