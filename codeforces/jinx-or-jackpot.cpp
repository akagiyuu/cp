#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<double> p(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		p[i] /= (double)100;
	}
	double res = 0;
	for (int i = 0; i < n; i++) {
		int cur = 1000 * (pow(1 + pow(2 * p -``)) - 1) - 1000;
		if (cur > 0)
			res += cur;
	}
	res /= (double)n;
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
