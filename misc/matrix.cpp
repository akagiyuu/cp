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
pair<vector<int>, vector<int> > build_lagrange(int k)
{
	int n = k + 2;
	vector<int> ys(n, 0);
	for (int i = 1; i < n; i++)
		ys[i] = add(ys[i - 1], powmod(i, k));
	int f = 1;
	for (int i = 1; i < n; i++)
		f = f * i % MOD;
	int v = powmod(f, MOD - 2);

	vector<int> inv(n, v);
	for (int i = n - 1; i > 0; i--)
		inv[i - 1] = inv[i] * i % MOD;

	vector<int> dp(n, 1);
	for (int i = 0; i < n; i++)
		dp[i] = inv[i] * inv[n - i - 1] % MOD * ys[i] % MOD;
	return { ys, dp };
}
int interpolate(int x, const vector<int> &ys, const vector<int> &dp)
{
	int n = ys.size();
	if (x < n)
		return ys[x];
	vector<int> X(n, 1), Y(n, 1);
	for (int i = 1; i < n; i++)
		X[i] = X[i - 1] * ((x - i + 1) % MOD) % MOD;
	for (int i = n - 2; i >= 0; i--)
		Y[i] = Y[i + 1] * ((x - i - 1) % MOD) % MOD;

	int res = 0;
	for (int i = 0; i < n; i++) {
		int w = X[i] * Y[i] % MOD * dp[i] % MOD;
		if ((n - i + 1) & 1)
			w = sub(0, w);
		res = add(res, w);
	}
	return res;
}

vector<int> ys_a, dp_a, ys_b, dp_b;

int calc_1(int x1, int x2, int y1, int y2, bool invert)
{
	if (x1 > x2 || y1 > y2)
		return 0;
	if (invert) {
		swap(x1, y1);
		swap(x2, y2);
	}
	int x = sub(interpolate(x2 + 1, ys_a, dp_a), interpolate(x1, ys_a, dp_a));
	int y = sub(interpolate(y2 + 1, ys_b, dp_b), interpolate(y1, ys_b, dp_b));
	return x * y % MOD;
}
int pre_2(int x, int y, int n)
{
	if (x < 0 || y < 0)
		return 0;
	x = min(x, 2 * n - 1);
	y = min(y, 2 * n - 1);

	int res = 0;
	res = add(res, calc_1(0, min(n - 1, x), 0, min(n - 1, y), false));
	if (x >= n)
		res = add(res, calc_1(0, x - n, 0, min(n - 1, y), true));
	if (y >= n)
		res = add(res, calc_1(0, min(n - 1, x), 0, y - n, true));
	if (x >= n && y >= n)
		res = add(res, calc_1(0, x - n, 0, y - n, false));
	return res;
}
int calc_2(int x1, int x2, int y1, int y2, int n)
{
	int res = pre_2(x2, y2, n);
	if (x1 > 0)
		res = sub(res, pre_2(x1 - 1, y2, n));
	if (y1 > 0)
		res = sub(res, pre_2(x2, y1 - 1, n));
	if (x1 > 0 && y1 > 0)
		res = add(res, pre_2(x1 - 1, y1 - 1, n));
	return res;
}
int pre_k(int x, int y, int n)
{
	if (x < 0 || y < 0)
		return 0;
	int m = 2 * n;

	int cnt_x = (x + 1) / m;
	int cnt_y = (y + 1) / m;
	int rem_x = (x + 1) % m;
	int rem_y = (y + 1) % m;

	int full = pre_2(m - 1, m - 1, n);

	int res = full * (cnt_x % MOD) % MOD * (cnt_y % MOD) % MOD;
	res = add(res, pre_2(rem_x - 1, m - 1, n) * (cnt_y % MOD) % MOD);
	res = add(res, pre_2(m - 1, rem_y - 1, n) * (cnt_x % MOD) % MOD);
	res = add(res, pre_2(rem_x - 1, rem_y - 1, n));

	return res;
}

void solve()
{
	int n, k, a, b;
	cin >> n >> k >> a >> b;
	tie(ys_a, dp_a) = build_lagrange(a);
	tie(ys_b, dp_b) = build_lagrange(b);

	int u, v, x, y;
	cin >> u >> v >> x >> y;
	u--;
	v--;
	x--;
	y--;

	int res = pre_k(x, y, n);
	if (u > 0)
		res = sub(res, pre_k(u - 1, y, n));
	if (v > 0)
		res = sub(res, pre_k(x, v - 1, n));
	if (u > 0 && v > 0)
		res = add(res, pre_k(u - 1, v - 1, n));
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
