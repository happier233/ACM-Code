const int N = int(1e6 + 100);

struct Node;
Node *tail, *null;
// 回收栈
Node *st[N], **stop;

struct Node {
    // 内存池
    static Node pool[N];

    Node *ch[2], *fa;
    bool rev, edit;
    int size, val;
    ll sum;
    ll dpl, dpr, dpm; // 左端开始最大，右端开始最大，实际最大

    // 初始化内存池
    static void init() {
        null = tail = pool;
        null->clear();
        stop = st;
    }

    // 清空当前
    inline void clear(int _val = 0, int _size = 0) {
        edit = rev = false;
        sum = val = _val;
        size = _size;
        fa = ch[0] = ch[1] = null;
        dpl = dpr = dpm = _val;
    }

    inline void push_up() {
        if (this == null) return;
        size = ch[0]->size + ch[1]->size + 1;
        sum = ch[0]->sum + ch[1]->sum + val;
        Node *x = ch[0], *y = ch[1];
        if (size == 1) {
            dpl = dpr = dpm = val;
        } else if (y == null) {
            dpl = max(x->dpl, x->sum + val);
            dpr = max(1ll * val, val + x->dpr);
            dpm = max(x->dpm, val + max(x->dpr, 0ll));
        } else if (x == null) {
            dpl = max(1ll * val, val + y->dpl);
            dpr = max(y->dpr, y->sum + val);
            dpm = max(y->dpm, val + max(y->dpl, 0ll));
        } else {
            dpl = max(x->dpl, max(x->sum + val, x->sum + val + y->dpl));
            dpr = max(y->dpr, max(y->sum + val, y->sum + val + x->dpr));
            dpm = max(max(x->dpm, y->dpm), val + max(x->dpr, 0ll) + max(y->dpl, 0ll));
        }
    }

    // 设置儿子
    inline void setc(Node *p, int d) { ch[d] = p, p->fa = this; }

    // 获取方向
    inline bool d() { return fa->ch[1] == this; }

    inline void update_rev() {
        if (this == null) return;
        swap(ch[0], ch[1]);
        swap(dpl, dpr);
        rev ^= 1;
    }

    inline void update_val(int v) {
        if (this == null) return;
        val = v;
        sum = 1ll * size * v;
        edit = 1;
        dpl = dpr = dpm = max(1ll * val, sum);
    }

    inline void push_down() {
        if (this == null) return;
        if (rev) {
            ch[0]->update_rev(), ch[1]->update_rev();
            rev = 0;
        }
        if (edit) {
            ch[0]->update_val(val), ch[1]->update_val(val);
            edit = 0;
        }
    }

    inline bool isroot() {
        return fa == null || (this != fa->ch[0] && this != fa->ch[1]);
    }
};

Node Node::pool[N];

// 获取第k个
Node *get_kth(Node *x, int k) {
    while (x->ch[0]->size + 1 != k) {
        x->push_down();
        if (x->ch[0]->size >= k) {
            x = x->ch[0];
        } else {
            k -= x->ch[0]->size + 1;
            x = x->ch[1];
        }
    }
    return x;
}

void rotate(Node *x) {
    Node *f = x->fa, *ff = f->fa;
    f->push_down();
    x->push_down();
    int c = x->d(), cc = f->d();
    f->setc(x->ch[!c], c);
    x->setc(f, !c);
    if (ff->ch[cc] == f) ff->setc(x, cc);
    else x->fa = ff;
    f->push_up();
}

void splay(Node *&root, Node *x, Node *goal) {
    for (Node *f; (f = x->fa) != goal; rotate(x)) {
        if (f->fa == goal) continue;
        f->fa->push_down();
        f->push_down();
        x->push_down();
        rotate(x->d() == f->d() ? f : x);
    }
    x->push_up();
    if (goal == null) root = x;
}

int a[N];

// 获取有效节点
inline Node *getNode() { return stop == st ? ++tail : *--stop; }

Node *build(int l, int r) {
    int mid = (l + r) >> 1;
    Node *root = getNode();
    root->clear();
    root->val = a[mid];
    root->size = 1;
    if (l < mid) root->setc(build(l, mid - 1), 0);
    if (r > mid) root->setc(build(mid + 1, r), 1);
    root->push_up();
    return root;
}

// l->root, r->root.ch[1]
inline Node *make(Node *&root, int l, int r) {
    Node *x = get_kth(root, l);
    splay(root, x, null);
    Node *y = get_kth(root, r);
    splay(root, y, root);
    return y;
}

// 插入p子树
inline void insert(Node *&root, int l, int r, Node *p) {
    Node *x = make(root, l, r);
    x->setc(p, 0);
    x->push_up();
    x->fa->push_up();
}

// 回收内存
inline void clear(Node *&x) {
    if (x == null) return;
    auto now = stop;
    *stop++ = x;
    while (now != stop) {
        x = *now++;
        if (x->ch[0] != null) *stop++ = x->ch[0];
        if (x->ch[1] != null) *stop++ = x->ch[1];
    }
}

// 释放子树
inline void del(Node *&root, int l, int r) {
    Node *x = make(root, l, r);
    clear(x->ch[0]);
    x->ch[0] = null;
    x->push_up();
    x->fa->push_up();
}

// 转向
inline void reverse(Node *&root, int l, int r) {
    Node *x = make(root, l, r);
    x->ch[0]->update_rev();
    x->push_up();
    x->fa->push_up();
}

// set value
inline void make_same(Node *&root, int l, int r, int val) {
    Node *x = make(root, l, r);
    x->ch[0]->update_val(val);
    x->push_up();
    x->fa->push_up();
}

// 求和
inline ll sum(Node *&root, int l, int r) {
    Node *x = make(root, l, r);
    return x->ch[0]->sum;
}

// 求最大子串和
inline ll maxsum(Node *&root, int l, int r) {
    Node *x = make(root, l, r);
    return x->ch[0]->dpm;
}

void debug(Node *root) {
    function<void(Node *)> dfs = [&dfs](Node *x) {
        if (x == null) return;
        x->push_down();
        dfs(x->ch[0]);
        cout << x->val << ' ';
        dfs(x->ch[1]);
    };
    dfs(root);
    cout << endl;
}