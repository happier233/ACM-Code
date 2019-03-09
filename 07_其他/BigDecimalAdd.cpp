#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;


void bigAdd(string a, string b, string &res)
{
	res = "";
	bool afu = false;
	bool bfu = false;
	if (a[0] == '-') {
		a = a.substr(1, a.length() - 1);
		afu = true;
	}
	if (b[0] == '-') {
		b = b.substr(1, b.length() - 1);
		bfu = true;
	}
	int len = (a.length() > b.length() ? a.length() : b.length());
	int * x = new int[len];
	memset(x, 0, sizeof(int)*len);
	int * y = new int[len];
	memset(y, 0, sizeof(int)*len);
	int t = 0;
	for (int i = a.length() - 1; i >= 0; i--) {
		x[t++] = (a[i] - '0')*(afu ? -1 : 1);
	}
	t = 0;
	for (int i = b.length() - 1; i >= 0; i--) {
		y[t++] = (b[i] - '0')*(bfu ? -1 : 1);
	}
	int * end = new int[len + 1];
	memset(end, 0, sizeof(int)*(len + 1));
	for (int i = 0; i < len; i++) {
		end[i] += (x[i] + y[i]);
		end[i + 1] += end[i] / 10;
		end[i] %= 10;
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
			end[i] += 10;
			end[i + 1]--;
		}
	}
	bool start = false;
	for (int i = len; i >= 0; i--) {
		if (start) {
			res += end[i] + '0';
		}
		else if (end[i] != 0) {
			start = true;
			res += end[i] + '0';
		}
	}
	if (!start) {
		res = "0";
	}
	delete[] x;
	delete[] y;
}

int main()
{
	string a[3], b[3];
	while (cin >> a[0] >> b[0]) {
		string result[2] = { "", "" };
		bool find = false;
		for (int i = a[0].length()-1; i >= 0; i--) {
			if (a[0][i] == '.') {
				a[1] = a[0].substr(0, i);
				a[2] = a[0].substr(i+1, a[0].length() - i - 1);
				find = true;
				break;
			}
		}
		if (!find) {
			a[1] = a[0];
			a[2] = "0";
		}
		find = false;
		for (int i = b[0].length() - 1; i >= 0; i--) {
			if (b[0][i] == '.') {
				b[1] = b[0].substr(0, i);
				b[2] = b[0].substr(i + 1, b[0].length() - i - 1);
				find = true;
				break;
			}
		}
		if (!find) {
			b[1] = b[0];
			b[2] = "0";
		}
		int back_len = (a[2].length() >= b[2].length() ? a[2].length() : b[2].length());
		for (int i = (a[2].length() - back_len); i > 0; i--){
			a[2] += '0';
		}
		for (int i = (b[2].length() - back_len); i > 0; i--) {
			b[2] += '0';
		}
		bigAdd(a[1], b[1], result[0]);
		bigAdd(a[2], b[2], result[1]);
		if (result[1].length() > back_len) {
			string t = "";
			bigAdd(result[0], t += result[1][0], result[0]);
			result[1].erase(result[1].begin());
		}
		for (int i = 0; i < back_len; i++) {
			if (result[1][i] == '0') {
				result[1] = result[1].substr(0, i);
			}
		}
		cout << result[0];
		if (result[1].length() > 0) {
			cout << '.' << result[1];
		}
		cout << endl;
 	}
	return 0;
}