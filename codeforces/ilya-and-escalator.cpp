#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const int MOD = 1000000007;

void solve()
{
	int n, t;
	double p;
	cin >> n >> p >> t;
	vector<vector<double> > dp(t + 1, vector<double>(n + 1, 0));
	for (int i = 1; i <= t; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = p * (dp[i - 1][j - 1] + 1) + (1 - p) * dp[i - 1][j];
		}
	}
	cout << fixed << setprecision(6) << dp[t][n] << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
