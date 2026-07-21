#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, m, k, d;
	cin >> n >> m >> k >> d;

	vector<int> cost(n), a(m), dp(m);
	multiset<int> ms;
	for (int i = 0; i < n; i++) {
		ms.clear();
		for (int j = 0; j < m; j++)
			cin >> a[j];
		dp[0] = a[0] + 1;
		ms.insert(dp[0]);
		for (int j = 1; j < m; j++) {
			dp[j] = *ms.begin() + a[j] + 1;
			ms.insert(dp[j]);
			if (j - d - 1 >= 0)
				ms.erase(ms.find(dp[j - d - 1]));
		}
		cost[i] = dp[m - 1];
	}

	int s = 0;
	for (int i = 0; i < k; i++) {
		s += cost[i];
	}
	int res = s;
	for (int i = k; i < n; i++) {
		s += cost[i];
		s -= cost[i - k];
		res = min(res, s);
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
