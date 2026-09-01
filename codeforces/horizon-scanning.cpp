#include <bits/stdc++.h>

using namespace std;

#define int long long

const double PI = acosl(-1.0L);

void solve()
{
	int n, k;
	cin >> n >> k;

	vector<double> angles(n);

	for (int i = 0; i < n; i++) {
		double x, y;
		cin >> x >> y;

		angles[i] = atan2(y, x);
	}

	sort(angles.begin(), angles.end());

	if (k == n) {
		cout << fixed << setprecision(10) << 2 * PI << '\n';
		return;
	}

	double res = 0;

	for (int i = 0; i < n; i++) {
		int j = i + k;
		double x = angles[i];
		double y = angles[j % n];
		if (j >= n)
			y += 2 * PI;
		res = max(res, y - x);
	}

	cout << fixed << setprecision(10) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;

	while (t--)
		solve();
}
