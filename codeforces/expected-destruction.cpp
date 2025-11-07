#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

int binpow(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

int inv(int a)
{
	return binpow(a, MOD - 2);
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	a.push_back(m + 1);
	n++;
	vector<vector<int> > dp(m + 2, vector<int>(m + 2));
	for (int i = 1; i <= m + 1; i++) {
		dp[i][i] = 0;
	}
	for (int i = 1; i <= m; i++) {
		dp[i][m + 1] = m + 1 - i;
	}

	auto inv2 = inv(2);
	for (int i = m + 1; i >= 1; i--) {
		for (int j = m; j >= i + 1; j--) {
			dp[i][j] = (dp[i + 1][j] + dp[i][j + 1] + 1) % MOD;
			dp[i][j] = dp[i][j] * inv2 % MOD;
		}
	}
	// for (int i = 1; i <= m + 1; i++) {
	// 	for (int j = i; j <= m + 1; j++) {
	// 		cout << dp[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }

	int res = 0;
	for (int i = 1; i < n; i++) {
		res += dp[a[i - 1]][a[i]];
		res %= MOD;
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
