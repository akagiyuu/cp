#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

int add(int a, int b)
{
	int res = a + b;
	return res < MOD ? res : res - MOD;
}

int sub(int a, int b)
{
	int res = a - b;
	return res < 0 ? res + MOD : res;
}

int mul(int a, int b)
{
	return a * b % MOD;
}

int powmod(int a, int b)
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

int invmod(int a)
{
	return powmod(a, MOD - 2);
}

vector<int> ys, dp;

void build_lagrange()
{
	int n = ys.size();

	int i, v, f;
	for (f = 1, i = 1; i < n; i++)
		f = mul(f, i);
	v = powmod(f, MOD - 2);

	vector<int> inv(n, v);
	for (i = n - 1; i > 0; i--) {
		inv[i - 1] = mul(inv[i], i);
	}

	dp.resize(n, 1);
	for (i = 0; i < n; i++) {
		dp[i] = mul(inv[i], inv[n - i - 1]);
		dp[i] = mul(dp[i], ys[i]);
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
		X[i] = mul(X[i - 1], (x - i + 1));

	for (i = n - 2; i >= 0; i--)
		Y[i] = mul(Y[i + 1], (x - i - 1));

	int res = 0;
	for (i = 0; i < n; i++) {
		w = mul(mul(X[i], Y[i]), dp[i]);
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
    ys.assign(k + 2, 0);
	for (int i = 1; i < k + 2; i++) {
		ys[i] = add(powmod(i, k), ys[i - 1]);
	}
    build_lagrange();
	int res = interpolate(n);
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
