#include <bits/stdc++.h>

using namespace std;

#define int long long

int MOD;

int add(int x, int y)
{
	x += y;
	if (x >= MOD)
		x -= MOD;
	return x;
}
int sub(int x, int y)
{
	x -= y;
	if (x < 0)
		x += MOD;
	return x;
}

void solve()
{
	int n, k;
	cin >> n >> k >> MOD;
	vector<vector<int> > dp(n + 2, vector<int>(k + 1, 0));
	dp[0][0] = 1;
	for (int i = 1; i <= n + 1; i++) {
		int s0 = 0;
		for (int y = 0; y <= k; y++)
			s0 = add(s0, dp[i - 1][y]);

		int s1 = 0, s2 = 0;
		for (int x = k; x >= 0; x--) {
			dp[i][x] = add(dp[i][x], s0);
			if (i == 1)
				continue;

			s1 = add(s1, dp[i - 2][k - x]);
			s2 = add(s2, (k - x) * dp[i - 2][k - x] % MOD);
			dp[i][x] = sub(dp[i][x], (k - x) * s1 % MOD);
			dp[i][x] = add(dp[i][x], s2);
		}
	}
	cout << dp[n + 1][0] << '\n';
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
