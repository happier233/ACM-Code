// 巴什博奕, 是否先手必胜
inline bool bash_game(int n, int m){
	//一堆东西, n个物品,最多选m个
	return n % (m + 1);
}
// 威佐夫博弈, 是否先手必胜
// 有两堆各若干的物品，两人轮流从其中一堆取至少一件物品，至多不限，或从两堆中同时取相同件物品，规定最后取完者胜利。
inline bool wythoff_game(int n, int m){
	if(n > m){
		int t = n;
		n = m;
		m = t;
	}
	int temp = floor((n2-n1)*(1+sqrt(5.0))/2.0);
	return temp != n1;
}

