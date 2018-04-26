template<class elemType>
inline void NEXT(elemType &T, vector<int>&next) {
	next[0] = -1;
	for (int i = 1; i < T.size(); i++) {
		int j = next[i - 1];
		while (j >= 0 && T[i - 1] != T[j]) j = next[j];
		if (j >= 0 && T[i - 1] == T[j]) next[i] = j + 1;
		else next[i] = 0;
	}
}

template<class elemType>
inline int COUNT_KMP(elemType &S, elemType &T) {
	vector<int>next(T.size());
	NEXT(T, next);
	int index, count = 0;
	for (index = 0; index < S.size(); ++index) {
		int pos = 0;
		int iter = index;
		while (pos < T.size() && iter < S.size()) {
			if (S[iter] == T[pos]) { ++iter; ++pos; }
			else {
				if (pos == 0) ++iter;
				else pos = next[pos - 1] + 1;
			}
		}
		if (pos == T.size() && (iter - index) == T.size()) ++count;
	}
	return count;
}

template<class elemType>
inline void NEXT(elemType T[], int count, vector<int>&next) {
	next[0] = -1;
	for (int i = 1; i < count; i++) {
		int j = next[i - 1];
		while (j >= 0 && T[i - 1] != T[j]) j = next[j];
		if (j >= 0 && T[i - 1] == T[j]) next[i] = j + 1;
		else next[i] = 0;
	}
}

template<class elemType>
inline int COUNT_KMP(elemType S[], int c1, elemType T[], int c2) {
	vector<int>next(c2);
	NEXT(T, c2, next);
	int index, count = 0;
	for (index = 0; index < c1; ++index) {
		int pos = 0;
		int iter = index;
		while (pos < c2 && iter < c1) {
			if (S[iter] == T[pos]) { ++iter; ++pos; }
			else {
				if (pos == 0) ++iter;
				else pos = next[pos - 1] + 1;
			}
		}
		if (pos == c2 && (iter - index) == c2) ++count;
	}
	return count;
}