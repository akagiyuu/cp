#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 1024;

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
	int n;
	cin >> n;
	vector<int> a(n), p(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int scale = inverse(10000);
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		p[i] = p[i] * scale % MOD;
	}
	vector<int> dp(N), ndp(N);
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		ndp.assign(N, 0);
		for (int s = 0; s < N; s++) {
			int ns = s ^ a[i];
			ndp[ns] = add(ndp[ns], dp[s] * p[i] % MOD);
			ndp[s] = add(ndp[s], dp[s] * sub(1, p[i]) % MOD);
		}
		dp = ndp;
	}
	int res = 0;
	for (int s = 1; s < N; s++) {
		res = add(res, s * s % MOD * dp[s] % MOD);
	}
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
