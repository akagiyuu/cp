#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ii pair<int, int>
#define fi first
#define se second

const int MOD = 998244353;

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

int cnt(int m, const vector<ii> &a)
{
	int n = a.size();
	vector<vector<int> > dp(n + 1, vector<int>(m + 1, 0));
	for (int j = 0; j <= m; j++)
		dp[0][j] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			int l = max(j - a[i - 1].se, 0ll);
			int r = j - a[i - 1].fi;
			if (l > r)
				continue;
			dp[i][j] = dp[i - 1][r];
			if (l > 0)
				dp[i][j] = sub(dp[i][j], dp[i - 1][l - 1]);
		}
		for (int j = 1; j <= m; j++) {
			dp[i][j] = add(dp[i][j], dp[i][j - 1]);
		}
	}
	return dp[n][m];
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<ii> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i].fi >> a[i].se;

	vector<int> mu(m + 1, 0);
	{
		vector<int> pr, cnt(m + 1, 0);
		vector<bool> is_composite(m + 1, false);
		mu[1] = 1;
		for (int i = 2; i <= m; i++) {
			if (!is_composite[i]) {
				pr.push_back(i);
				mu[i] = -1;
				cnt[i] = 1;
			}
			for (int j = 0; j < (int)pr.size() && i * pr[j] <= m; j++) {
				int p = pr[j];

				is_composite[i * p] = true;
				if (i % p == 0) {
					mu[i * p] = 0;
				} else {
					mu[i * p] = mu[i] * mu[p];
					cnt[i * p] = 1;
				}
			}
		}
		for (int i = 1; i <= m; i++)
			if (mu[i] == -1)
				mu[i] = MOD - 1;
	}
	int res = 0;
	for (int d = 1; d <= m; d++) {
		vector<ii> b(n);
		for (int i = 0; i < n; i++) {
			b[i].fi = (a[i].fi + d - 1) / d;
			b[i].se = a[i].se / d;
		}
		res = add(res, mu[d] * cnt(m / d, b) % MOD);
	}
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
