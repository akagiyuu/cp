#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}

	auto cost = [a, b](int l, int r) { return abs(a[l] - b[r]) + abs(a[r] - b[l]); };

	vector<vector<int> > dp(n + 1, vector<int>(n + 1, 0));
	dp[1][1] = cost(1, 1);
	for (int i = 2; i < n; i++) {
		for (int len = 1; len <= i + 1; len++) {
			for (int j = i; j >= 1; j--) {
				int cur_len = i - j + 1;
				if (cur_len > len)
					break;
				dp[i][len] = max(dp[i][len], cost(j, i) + dp[i - cur_len][len - cur_len]);
			}
		}
	}
	// for (int i = 0; i < n; i++) {
	// 	for (int len = 0; len < n + 1; len++) {
	// 		cout << dp[i][len] << " ";
	// 	}
	// 	cout << "\n";
	// }

	int res = 0;
	for (int i = 0; i < n; i++) {
		res = max(res, dp[i][k]);
	}
	cout << res << "\n";
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
