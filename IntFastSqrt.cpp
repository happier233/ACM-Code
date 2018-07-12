int sqrtI(int t)
{
	int min = 0;
	int max = t;
	while (min != max && min + 1 != max) {
		int mid = (min + max) / 2;
		int a = mid * mid;
		if (a == t) {
			return mid;
		}
		else if (a > t) {
			max = mid;
		}
		else if (a < t) {
			min = mid;
		}
	}
	return min;
}