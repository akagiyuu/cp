#include <bits/stdc++.h>

using namespace std;

#define int long long

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
	int n, S;
	cin >> n >> S;
	vector<int> a(n + 1), p(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> p[i];

	vector<int> b(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		if (a[i] == 0)
			continue;
		b[i] = 1;
		for (int j = i; j <= n; j += i) {
			a[j] = (a[j] + 1) % 2;
		}
	}
	vector<vector<int> > dp(S + 1, vector<int>(2, 0));
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int s = S; s >= p[i]; s--) {
			for (int j = 0; j < 2; j++) {
				dp[s][j] = add(dp[s][j], dp[s - p[i]][b[i] ^ j]);
			}
		}
	}
	int res = 0;
	for (int s = 1; s <= S; s++) {
		res = add(res, dp[s][1] * inverse(s) % MOD);
	}
	res = res * S % MOD;

	cout << res << '\n';
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
