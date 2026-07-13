#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 2e5 + 1;

int cnt[N], dp[N];

void solve()
{
	fill(cnt, cnt + N, 0);
	fill(dp, dp + N, 0);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		cnt[x]++;
	}

	int res = 1;
	vector<int> dp(N, 0);
	for (int x = 1; x < N; x++) {
		if (cnt[x] == 0)
			continue;

		dp[x] = max(dp[x], cnt[x]);
		res = max(res, dp[x]);

		for (int y = 2 * x; y < N; y += x) {
			if (cnt[y] == 0)
				continue;
			dp[y] = max(dp[y], dp[x] + cnt[y]);
		}
	}

	cout << n - res << "\n";
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
