template<class T>

struct TreeNode {
    T value;
    TreeNode *left;
    TreeNode *right;
};

template<class T>
TreeNode<T> *createTree(const T *pre, const T *in, const int len) {
    TreeNode<T> *t = NULL;
    if (len > 0) {
        t = new TreeNode<T>;
        t->value = pre[0];
        int index;
        for (index = 0; index < len; index++) {
            if (in[index] == pre[0]) {
                break;
            }
        }
        if (index == len) {
            index = -1;
        }
        t->left = createTree(pre + 1, in, index);
        t->right = createTree(pre + index + 1, in + index + 1, len - index - 1);
    }
    return t;
}

template<class T>
int preOrder(TreeNode<T> *root, queue<T> &out) {
    if (root) {
        int count = 1;
        out.push(root->value);
        count += preOrder(root->left, out);
        count += preOrder(root->right, out);
        return count;
    } else {
        return 0;
    }
}

template<class T>
int inOrder(TreeNode<T> *root, queue<T> &out) {
    if (root) {
        int count = 1;
        count += inOrder(root->left, out);
        out.push(root->value);
        count += inOrder(root->right, out);
        return count;
    } else {
        return 0;
    }
}

template<class T>
void postOrder(TreeNode<T> *root, queue<T> &out) {
    if (root) {
        postOrder(root->left, out);
        postOrder(root->right, out);
        out.push(root->value);
    } else {
        return;
    }
}

template<class T>
T *convertQueueToArray(queue<T> &out, int len) {
    T *list = new T[len];
    int now = 0;
    while (!out.empty() && now < len) {
        list[now] = out.front();
        out.pop();
        now++;
    }
    return list;
}

template<class T>
void destroyTree(TreeNode<T> *root) {
    if (root) {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    } else return;
}

template<class T>
void insertIntoBSTree(TreeNode<T> *root, const T &value) {
    if (!root) {
        return;
    }
    if (value < root->value) {
        if (root->left) {
            insertIntoTree(root->left, value);
        } else {
            root->left = new TreeNode<T>;
            root->left->value = value;
            root->left->left = NULL;
            root->left->right = NULL;
        }
    } else if (value > root->value) {
        if (root->right) {
            insertIntoTree(root->right, value);
        } else {
            root->right = new TreeNode<T>;
            root->right->value = value;
            root->right->left = NULL;
            root->right->right = NULL;
        }
    }
}

template<class T>
TreeNode<T> *createBSTree(T *list, int len) {
    if (len < 1) {
        return NULL;
    }
    TreeNode<T> *root = new TreeNode<char>;
    root->value = list[0];
    root->left = NULL;
    root->right = NULL;
    for (int i = 1; i < len; i++) {
        insertIntoBSTree(root, list[i]);
    }
    return root;
}