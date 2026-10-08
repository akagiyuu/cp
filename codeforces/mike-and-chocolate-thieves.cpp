#include <bits/stdc++.h>

using namespace std;

#define int long long

int f(int n)
{
	int res = 0;
	int sz = (int)ceil(pow(n, 1. / 3.)) + 7;
	for (int k = 2; k <= sz; k++) {
		res += n / (k * k * k);
	}
	return res;
}

int solve()
{
	int m;
	cin >> m;
	int l = 8, r = 1e18;
	int res = -1;
	while (l <= r) {
		int mid = (l + r) / 2;
		int cur = f(mid);
		if (cur >= m) {
			if (cur == m)
				res = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	if (res != -1 && f(res) == m)
		return res;
	return -1;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << '\n';
}
