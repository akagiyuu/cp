#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;
const int N = 2e5 + 7;

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
	for (int i = N - 2; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}
int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * ifact[n - k] % MOD * ifact[k] % MOD;
}

void solve()
{
	int m, n;
	cin >> m >> n;
	int mx_k = min(__lg(m) + 1, n);
	vector<vector<int> > dp(mx_k + 1, vector<int>(m + 1, 0));
	for (int x = 1; x <= m; x++)
		dp[1][x] = 1;
	for (int k = 1; k < mx_k; k++) {
		for (int x = 1; x <= m; x++) {
			for (int y = x * 2; y <= m; y += x) {
				dp[k + 1][y] = add(dp[k + 1][y], dp[k][x]);
			}
		}
	}
	// for (int x = 2; x <= m; x++) {
	// 	cout << x << " -> ";
	// 	for (int k = 1; k <= mx_k; k++) {
	// 		cout << dp[k][x] << ' ';
	// 	}
	// 	cout << '\n';
	// }
	int res = 0;
	for (int x = 1; x <= m; x++) {
		int cur = sub(C(m - x, n - 1), C(m / x - 1, n - 1)) * n % MOD;
		res = add(res, cur);
	}
	for (int k = 1; k <= mx_k; k++) {
		for (int x = 1; x <= m; x++) {
			int cur = 0;
			for (int y = x * 2; y <= m; y += x) {
				cur = add(cur, sub(C(m / x - y / x, n - k - 1), C(m / y - 1, n - k - 1)));
			}
			cur = cur * dp[k][x] % MOD * (n - k) % MOD;
			res = add(res, cur);
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
