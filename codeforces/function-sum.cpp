#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;
const int N = 100;

int add(int T, int y)
{
	T += y;
	if (T >= MOD)
		T -= MOD;
	return T;
}
int sub(int T, int y)
{
	T -= y;
	if (T < 0)
		T += MOD;
	return T;
}
int powmod(int T, int e)
{
	int r = 1;
	while (e) {
		if (e & 1)
			r = r * T % MOD;
		T = T * T % MOD;
		e >>= 1;
	}
	return r;
}
int inverse(int T)
{
	return powmod(T, MOD - 2);
}

int c[N][N + 1];
void build()
{
	for (int i = 0; i < N; i++) {
		c[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			c[i][j] = add(c[i - 1][j], c[i - 1][j - 1]);
		}
	}
}
int C(int n, int k)
{
	if (n < 0)
		return 1;
	if (k < 0 || k > n)
		return 0;
	return c[n][k];
}

vector<int> ys, dp;
void build_lagrange()
{
	int n = ys.size(), i, v, f;
	for (f = 1, i = 1; i < n; i++)
		f = f * i % MOD;
	v = powmod(f, MOD - 2);
	vector<int> inv(n, v);
	for (i = n - 1; i > 0; i--)
		inv[i - 1] = inv[i] * i % MOD;
	dp.resize(n, 1);
	for (i = 0; i < n; i++) {
		dp[i] = inv[i] * inv[n - i - 1] % MOD;
		dp[i] = dp[i] * ys[i] % MOD;
	}
}
int interpolate(long long x)
{
	int n = ys.size();
	if (x < n)
		return ys[x];
	int i, w;
	vector<int> X(n, 1), Y(n, 1);
	for (i = 1; i < n; i++)
		X[i] = X[i - 1] * (x - i + 1) % MOD;
	for (i = n - 2; i >= 0; i--)
		Y[i] = Y[i + 1] * (x - i - 1) % MOD;
	int res = 0;
	for (i = 0; i < n; i++) {
		w = X[i] * Y[i] % MOD * dp[i] % MOD;
		if ((n - i + 1) & 1)
			w = sub(0, w);
		res = add(res, w);
	}
	return res;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	k--;
	auto f = [&n](int k) {
		int res = 0;
		for (int t = 0; t <= k; t++) {
			for (int i = 0; i < n - 1; i++) {
				for (int s1 = 0; s1 <= i; s1++) {
					for (int s2 = s1 + 1; s2 <= n - i - 1; s2++) {
						int l = C(i, s1) * powmod(t, s1) % MOD * powmod(k - t + 1, i - s1) %
							MOD;
						int r = C(n - 1 - i, s2) * powmod(k - t, s2) % MOD *
							powmod(t + 1, n - 1 - i - s2) % MOD;
						int cur = l * r % MOD * (t + 1) % MOD;
						res = add(res, cur);
					}
				}
			}
		}
		return res;
	};
	ys.resize(n + 3);
	for (int i = 0; i <= n + 2; i++)
		ys[i] = f(i);
	build_lagrange();
	cout << interpolate(k) << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
