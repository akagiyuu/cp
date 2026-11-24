#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

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
int powmod(int x, int e)
{
	int r = 1;
	while (e) {
		if (e & 1)
			r = r * x % MOD;
		x = x * x % MOD;
		e >>= 1;
	}
	return r;
}
int inverse(int x)
{
	return powmod(x, MOD - 2);
}

void solve()
{
	int n, d;
	cin >> n >> d;

	int m = 1;
	for (int i = 0; i < d; i++)
		m *= 10;

	// vector<vector<int> > dp(n + 1, vector<int>(m, 1));
	// for (int i = 1; i <= n; i++)
	// 	dp[i][0] = 1;
	// for (int j = 1; j < m; j++)
	// 	dp[0][j] = 1;
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j < m; j++) {
	// 		dp[i][j] = add(dp[i][j - 1], (m - j + 1) * dp[i - 1][j] % MOD);
	// 	}
	// }
	// cout << dp[n][m - 1] << '\n';

	vector<int> fact(m), ifact(m);
	fact[0] = 1;
	for (int i = 1; i < m; i++)
		fact[i] = fact[i - 1] * i % MOD;
	ifact[m - 1] = inverse(fact[m - 1]);
	for (int i = m - 2; i >= 0; i--)
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;

	int res = 0;
	for (int i = 1; i <= m; i++) {
		int cur = powmod(i, n) * powmod(i, m - 1) % MOD;
		cur = cur * ifact[i - 1] % MOD * ifact[m - i] % MOD;
		if ((m - i) % 2 == 0)
			res = add(res, cur);
		else
			res = sub(res, cur);
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
