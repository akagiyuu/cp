#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

void solve()
{
	int h, w, n;
	cin >> h >> w >> n;

	vector<vector<int> > dp(h, vector<int>(w, -1));
	for (int i = 0; i < n; i++) {
		int r, c;
		cin >> r >> c;
		r--;
		c--;
		dp[h - 1 - r][w - 1 - c] = 0;
	}
	dp[0][0] = 1;
	int max_dist = (h - 1) + (w - 1);
	for (int dist = 1; dist <= max_dist; dist++) {
		for (int i = 0; i <= min(h - 1, dist); i++) {
			int j = dist - i;
			if (j >= w)
				continue;
			if (dp[i][j] != -1)
				continue;
			dp[i][j] = 0;
			if (j >= 1)
				dp[i][j] = dp[i][j] + dp[i][j - 1] % MOD;
			if (i >= 1)
				dp[i][j] = dp[i][j] + dp[i - 1][j] % MOD;
		}
	}
	cout << dp[h - 1][w - 1] << "\n";
}

signed main()
{
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
	// cout.tie(NULL);

	solve();
}
