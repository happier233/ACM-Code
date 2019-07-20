vector<int> dist;
vector<vector<node>> eg;
vector<int> path;

bool spfa(int n, int start) {
    dist.assign(n, INF);
    dist[start] = 0;
    deque<int> q;
    q.push_back(start);
    path.assign(n, -1);
    vector<int> cnt(n, 0);
    vector<bool> flag(n, false);
    cnt[start] = flag[start] = true;
    while (!q.empty()) {
        const int now = q.front();
        q.pop_front();
        flag[now] = false;
        for (auto i: eg[now]) {
            if (dist[i.x] > dist[now] + i.d) {
                dist[i.x] = dist[now] + i.d;
                path[i.x] = now;
                if (!flag[i.x]) {
                    if (n == ++cnt[i.x]) return false;
                    //队列非空且优于队首（SLF）
                    if (!q.empty() && dist[i.x] < dist[q.front()]) {
                        q.push_front(i.x);
                    } else {
                        q.push_back(i.x);
                    }
                    flag[i.x] = true;
                }
            }
        }
    }
    return true;
}
