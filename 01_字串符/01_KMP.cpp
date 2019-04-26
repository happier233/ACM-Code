template<class elemType>
inline void kmp_nxt(elemType &T, vector<int> &nxt) {
    nxt[0] = -1;
    for (int i = 1; i < T.size(); i++) {
        int j = nxt[i - 1];
        while (j >= 0 && T[i - 1] != T[j]) j = nxt[j];
        if (j >= 0 && T[i - 1] == T[j]) nxt[i] = j + 1;
        else nxt[i] = 0;
    }
}

template<class elemType>
inline int kmp_count(elemType &S, elemType &T) {
    vector<int> nxt(T.size());
    kmp_nxt(T, nxt);
    int index, count = 0;
    for (index = 0; index < S.size(); ++index) {
        int pos = 0;
        int iter = index;
        while (pos < T.size() && iter < S.size()) {
            if (S[iter] == T[pos]) {
                ++iter;
                ++pos;
            } else {
                if (pos == 0) ++iter;
                else pos = nxt[pos - 1] + 1;
            }
        }
        if (pos == T.size() && (iter - index) == T.size()) ++count;
    }
    return count;
}

template<class elemType>
inline void kmp_next(elemType T[], int count, vector<int> &nxt) {
    nxt[0] = -1;
    for (int i = 1; i < count; i++) {
        int j = nxt[i - 1];
        while (j >= 0 && T[i - 1] != T[j]) j = nxt[j];
        if (j >= 0 && T[i - 1] == T[j]) nxt[i] = j + 1;
        else nxt[i] = 0;
    }
}

template<class elemType>
inline int kmp_count(elemType S[], int c1, elemType T[], int c2) {
    vector<int> nxt(c2);
    kmp_nxt(T, c2, nxt);
    int index, count = 0;
    for (index = 0; index < c1; ++index) {
        int pos = 0;
        int iter = index;
        while (pos < c2 && iter < c1) {
            if (S[iter] == T[pos]) {
                ++iter;
                ++pos;
            }
            else {
                if (pos == 0) ++iter;
                else pos = nxt[pos - 1] + 1;
            }
        }
        if (pos == c2 && (iter - index) == c2) ++count;
    }
    return count;
}