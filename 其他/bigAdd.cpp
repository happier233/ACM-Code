#include <string>
#include <cstring>

using namespace std;

int convertTo(const char &a)
{
	if (a >= '0' && a <= '9') {
		return a - '0';
	}
	else if (a >= 'A' && a <= 'Z') {
		return a - 'A' + 10;
	}
	else if (a >= 'a' && a <= 'z') {
		return a - 'a' + 10;
	}
}

string& bigAdd(const string &m, const string &n, string &res, int base)
{
	string a = m;
	string b = n;
	res = "";
	bool afu = false;
	bool bfu = false;
	if (a[0] == '-') {
		a = a.substr(1, a.length() - 1);
		afu = true;
	}
	else if (a[0] == '+') {
		a = a.substr(1, a.length() - 1);
	}
	if (b[0] == '-') {
		b = b.substr(1, b.length() - 1);
		bfu = true;
	}
	else if (b[0] == '+') {
		b = b.substr(1, b.length() - 1);
	}
	int len = (a.length() > b.length() ? a.length() : b.length());
	int * x = new int[len];
	memset(x, 0, sizeof(int)*len);
	int * y = new int[len];
	memset(y, 0, sizeof(int)*len);
	int t = 0;
	for (int i = a.length() - 1; i >= 0; i--) {
		x[t++] = convertTo(a[i])*(afu ? -1 : 1);
	}
	t = 0;
	for (int i = b.length() - 1; i >= 0; i--) {
		y[t++] = convertTo(b[i])*(bfu ? -1 : 1);
	}
	int * end = new int[len + 1];
	memset(end, 0, sizeof(int)*(len + 1));
	for (int i = 0; i < len; i++) {
		end[i] += (x[i] + y[i]);
		end[i + 1] += end[i] / base;
		end[i] %= base;
	}
	bool check = false;
	for (int i = len; i >= 0; i--) {
		if (end[i] > 0) {
			break;
		}
		else if (end[i] < 0) {
			check = true;
			break;
		}
	}
	if (check) {
		for (int i = len; i >= 0; i--) {
			end[i] = -end[i];
		}
		res += '-';
	}
	for (int i = 0; i < len; i++) {
		if (end[i] < 0) {
			end[i] += base;
			end[i + 1]--;
		}
	}
	bool start = false;
	for (int i = len; i >= 0; i--) {
		if (start) {
			res += "0123456789ABCDEF"[end[i]];
		}
		else if (end[i] != 0) {
			start = true;
			res += "0123456789ABCDEF"[end[i]];
		}
	}
	if (!start) {
		res = "0";
	}
	delete[] x;
	delete[] y;
	return res;
}