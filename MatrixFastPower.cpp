#define MAX_N 10
#define mod_num 9973

struct Mat {
	long long mat[MAX_N][MAX_N];
	long long n;
	Mat() {
		memset(mat, 0, sizeof(mat));
		n = 0;
	}
	Mat(long long n) {
		memset(mat, 0, sizeof(mat));
		this->n = n;
	}
	void init() {
		for (int i = 0; i < n; ++i) {
			mat[i][i] = 1;
		}
	}
	Mat(const long long ** list, long long n) {
		this->n = n;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				mat[i][j] = list[i][j];
			}
		}
	}
};

Mat operator * (Mat a, Mat b) {
	long long n = a.n;
	Mat c(n);
	memset(c.mat, 0, sizeof(c.mat));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				c.mat[i][j] += (a.mat[i][k] * b.mat[k][j]) % mod_num;
				c.mat[i][j] %= mod_num;
			}
		}
	}
	return c;
}

Mat operator ^ (Mat a, int k) {
	long long n = a.n;
	Mat c(n);
	c.init();
	for (; k; k >>= 1) {
		if (k & 1)   c = c * a;
		a = a * a;
	}
	return c;
}