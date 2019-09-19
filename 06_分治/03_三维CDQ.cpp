struct node {
    // time: 时间 | id: 0,1 是否修改 | f: 正负 | x是下标 | y是权值
    int time, id, f, x, y;
};

bool cmp(const node &a, const node &b) {
    return a.x < b.x;
}

int ans[N];
node p[N << 2], et[N << 2];

void cdq(int l, int r) {
    if (l + 1 == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid, r);
    int t = l;
    for (int i = mid; i < r; i++) {
        // if edit continue
        if (p[i].id)continue;
        for (; t < mid && p[t].x <= p[i].x; t++) {
            if (p[t].id) tree.change(p[t].y, p[t].f);;
        }
        int f = p[i].f;
        int cnt = tree.query(p[i].y);
        ans[p[i].time] += f * cnt;
    }
    // 逆操作p[t].y
    while (--t >= l) {
        if (p[t].id) tree.change(p[t].y, -p[t].f);
    }
    // 归并排序
    int t1 = l, t2 = mid, k = 0;
    while (t1 < mid && t2 < r) {
        et[k++] = p[t1].x < p[t2].x ? p[t1++] : p[t2++];
    }
    copy(p + t1, p + mid, et + k);
    copy(p + t2, p + r, et + k);
    copy(et, et + (r - l), p + l);
}