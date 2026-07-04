#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int m, n;
	cin >> m >> n;
	double res = 0;
	for (int M = 1; M <= m; M++) {
		double a = (double)M / (double)m;
		a = pow(a, n);
		double b = (double)(M - 1) / (double)m;
		b = pow(b, n);
		res += (a - b) * (double)M;
	}
	cout << setprecision(10) << fixed << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
