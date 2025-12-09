#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve()
{
	int n, k, g1, g2, g3;
	cin >> n >> k >> g1 >> g2 >> g3;
	string s;
	cin >> s;
	s = "#" + s;
	vector<vector<int> > dp(n + 1, vector<int>(k + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			dp[i][j] = dp[i - 1][j];
			if (s[i] == '#') {
				continue;
			}
			if (j >= 1)
				dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + g1);
			if (i <= 1)
				continue;
			if (s[i - 1] == '.') {
				dp[i][j] = max(dp[i][j], dp[i - 2][j] + g2);
			}
			if (i <= 2)
				continue;
			if (s[i - 1] == '#' && s[i - 2] == '.') {
				dp[i][j] = max(dp[i][j], dp[i - 3][j] + g3);
			}
		}
	}
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= k; j++) {
	// 		cout << dp[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }
	cout << dp[n][k] << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
