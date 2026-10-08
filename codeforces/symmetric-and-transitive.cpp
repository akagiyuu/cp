#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 4e3 + 7;
const int MOD = 1000000007;

int fact[N], ifact[N];

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

void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % MOD;
	ifact[N - 1] = inverse(fact[N - 1]);
	for (int i = N - 2; i >= 0; i--)
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}
int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * ifact[n - k] % MOD * ifact[k] % MOD;
}

void solve()
{
	int n;
	cin >> n;
	vector<vector<int> > dp(n, vector<int>(n, 0));
	dp[0][0] = 1;
	for (int k = 1; k < n; k++) {
		dp[k][k] = 1;
		for (int x = k + 1; x < n; x++) {
			dp[k][x] = add(dp[k][x], k * dp[k][x - 1] % MOD);
			dp[k][x] = add(dp[k][x], dp[k - 1][x - 1]);
		}
	}
	int res = 0;
	for (int k = 0; k < n; k++) {
		for (int x = k; x < n; x++) {
			res = add(res, dp[k][x] * C(n, x) % MOD);
		}
	}
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
