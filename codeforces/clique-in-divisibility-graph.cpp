#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 1e6 + 1;

bool exist[N];
int dp[N];

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		exist[a[i]] = true;
	}

	int res = 1;
	for (auto x : a) {
		dp[x] = max(dp[x], 1ll);
		res = max(res, dp[x]);
		for (int y = 2 * x; y < N; y += x) {
			if (!exist[y])
				continue;
			dp[y] = max(dp[y], 1 + dp[x]);
		}
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
