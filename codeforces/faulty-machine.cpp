#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

double C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	if (n - k < k)
		k = n - k;
	double res = 1;
	for (int i = 1; i <= k; i++)
		res = res * (double)(n - k + i) / i;
	return res;
}

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	double total = C(n, m);

	vector<vector<double> > A(n);
	vector<int> left(n), right(n);
	for (int x = 0; x <= n; x++) {
		if (x == k)
			continue;
		int id = x - (x >= k);

		left[id] = max(x - m, 0ll);
		right[id] = min(x + m, n);
		A[id].assign(right[id] - left[id] + 1, 0);
		for (double t = m; t >= 0; t--) {
			double p = C(x, t) * C(n - x, m - x) / total;
			if (p == 0)
				continue;

			int y = x + m - 2 * t;
			if (y < 0 || y > n)
				continue;

			if (y == x)
				eq.push_back({ y, 1 - p });
			else
				eq.push_back({ y, -p });
		}
	}

	vector<double> b(n, 1);
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
