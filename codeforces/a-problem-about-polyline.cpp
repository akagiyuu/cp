#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const double INF = 1e32;

void solve()
{
	double res = INF;
	double a, b;
	cin >> a >> b;

	double k = floor((a - b) / (2. * b));
	if (k >= 0) {
		double x = (a - b) / (2. * k);
		res = min(res, x);
	}

	k = floor((a + b) / (2. * b));
	if (k >= 0) {
		double x = (a + b) / (2. * k);
		res = min(res, x);
	}

	if (res == INF)
		cout << -1 << '\n';
	else
		cout << fixed << setprecision(10) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
