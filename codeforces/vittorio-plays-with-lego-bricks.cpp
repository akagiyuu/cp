#include <bits/stdc++.h>

using namespace std;

#define int long long

const int INF = 1e18;

void solve()
{
	int n, h;
	cin >> n >> h;
	vector<int> x(n);
	for (int i = 0; i < n; i++)
		cin >> x[i];
	vector<vector<int> > dp(n, vector<int>(n, INF));
	for (int l = n - 1; l >= 0; l--) {
		dp[l][l] = h;
		for (int r = l + 1; r < n; r++) {
			int x1 = x[l], x2 = x[r];
			// x1 + h0 + 2 >= x2 - h0
			int h0 = x2 - x1 - 2;
			if (h0 < 0)
				h0 = 0;
			else
				h0 = (h0 + 1) / 2;
			h0 = max(h - h0, 0ll);
			for (int m = l; m < r; m++) {
				dp[l][r] = min(dp[l][r], dp[l][m] + dp[m + 1][r] - h0);
			}
		}
	}
	cout << dp[0][n - 1] << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
