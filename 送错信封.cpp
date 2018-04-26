#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int main()
{
	long long table[21] = { 0,0,1 };
	for (int i = 3; i <= 20; i++) {
		table[i] = (i - 1)*(table[i - 1] + table[i - 2]);
	}
	int n, t;
	while (cin >> n) {
		for (int i = 1; i <= n; i++) {
			cin >> t;
			cout << table[t] << endl;
		}
	}
	return 0;
}