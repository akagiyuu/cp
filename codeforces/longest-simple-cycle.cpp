#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> c(n), a(n - 1), b(n - 1);
	for (int i = 0; i < n; i++)
		cin >> c[i];
	int _tmp;
	cin >> _tmp;
	for (int i = 0; i < n - 1; i++)
		cin >> a[i];
	cin >> _tmp;
	for (int i = 0; i < n - 1; i++)
		cin >> b[i];

	vector<int> dp(n);
	dp[n - 2] = c[n - 1] - 1 + abs(a[n - 2] - b[n - 2]) + 2;
	// cout << dp[n - 2] << " ";
	for (int i = n - 3; i >= 0; i--) {
		int last = abs(a[i] - b[i]) + 2;

		dp[i] = c[i + 1] - 1 + last;
		// cout << dp[i] << " ";
		if (a[i + 1] == b[i + 1])
			continue;

		dp[i] = max(dp[i], dp[i + 1] - abs(a[i + 1] - b[i + 1]) + min(a[i + 1], b[i + 1]) - 1 + c[i + 1] -
					   max(a[i + 1], b[i + 1]) + last);
	}
	// cout << "\n";
	int res = 0;
	for (int i = n - 2; i >= 0; i--) {
		// cout << dp[i] << " ";
		res = max(res, dp[i]);
	}
	// cout << "\n";
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
