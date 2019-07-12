int dist[N];
int path[N];

void bfs(int s, int n) {
    n++;
    rep(i, 0, n) dist[i] = INF;
    memset(path, -1, sizeof(int) * n);
    dist[s] = 0;
    path[s] = s;
	// 注意优先队列默认less运算，但选择最大的作为top，注意cmp！！！
    priority_queue<Edge, vector<Edge>, greater<Edge>> q;
    q.push(Edge(s, dist[s]));
    while (!q.empty()) {
        Edge f = q.top();
        q.pop();
        for (int i = gh.head[f.e]; ~i; i = gh.eg[i].nxt) {
            Edge &t = gh.eg[i];
            if (dist[t.e] > f.v + t.v) {
                dist[t.e] = f.v + t.v;
                path[t.e] = f.e;
                q.push(Edge(t.e, dist[t.e]));
            }
        }
    }
}

#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
typedef __gnu_pbds::priority_queue<Edge, greater<Edge>> heap;
// 使用该模板，需要注意因为使用了greater，所以需要重载大于运算
// 默认pairing_heap_tag
// push O(1), pop O(logn) modify O(logn) erase O(logn) join O(1)
// 可选thin_heap_tag
// push O(1), pop O(logn) modify O(1) erase O(logn) join O(n)

heap::point_iterator its[N];
int cnt[N];

void bfs(int s, int n) {
    n++;
    rep(i, 0, n) dist[i] = INF;
    memset(cnt, 0, sizeof(int) * n);
    dist[s] = 0;
    cnt[s] = 1;
    heap q;
    its[s] = q.push(Edge(s, dist[s]));
    while (!q.empty()) {
        Edge f = q.top();
        q.pop();
        for (int i = gh.head[f.e]; ~i; i = gh.eg[i].nxt) {
            Edge &t = gh.eg[i];
            its[t.e] = 0;
            int v = f.v + t.v;
            if (dist[t.e] > v) {
                dist[t.e] = v;
                if (its[t.e] != 0) {
                    q.modify(its[t.e], Edge(t.e, dist[t.e]));
                } else {
                    its[t.e] = q.push(Edge(t.e, dist[t.e]));
                }
                cnt[t.e] = cnt[f.e];
            } else if (dist[t.e] == v) {
                (cnt[t.e] += cnt[f.e]) %= 100003;
            }
        }
    }
}