#define INF 10000000

struct node {
    int x, d;
    node() {};
    node(int a, int b) {
        x = a;
        d = b;
    }
    bool operator<(const node &a) const {
        return (a.d == d ? x < a.x : d < a.d);
    }
};

#define N_MAX 150
vector<node> eg[N_MAX];
int dist[N_MAX];
vector<int> path[N_MAX];

void dfs(int s, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    priority_queue<node> list;
    list.push(node(s, dist[s]));
    while (!list.empty()) {
        node x = list.top();
        list.pop();
        for (vector<node>::iterator i = eg[x.x].begin(); i != eg[x.x].end(); i++) {
            node y = *i;
            if (dist[y.x] > x.d + y.d) {
                dist[y.x] = x.d + y.d;
                path[y.x] = path[x.x];
                path[y.x].push_back(y.x);
                list.push(node(y.x, dist[y.x]));
            }
        }
    }
}