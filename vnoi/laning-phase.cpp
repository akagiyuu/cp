#include <bits/stdc++.h>

#define int long long

using namespace std;

bool solve()
{
	int n, x, y, a, b;
	cin >> n >> x >> y >> a >> b;
	int diff = y - x;
	if (a > b && diff > 1) {
		return true;
	}
	if (a > b && diff == 1) {
		int left = x - 1;
		if (left >= b + 1)
			return true;
		else
			return false;
	}
	if (a < b && diff > a + 1) {
		return false;
	}
	if (a < b && diff == 1) {
		return false;
	}
	if (a < b && diff <= a + 1) {
		int right = n - y;
		if (right >= a + 1)
			return false;
		else
			return true;
	}

	return diff % (a + 1) != 1;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		if (solve()) {
			cout << "Kiaya\n";
		} else {
			cout << "Zeros\n";
		}
	}
}
