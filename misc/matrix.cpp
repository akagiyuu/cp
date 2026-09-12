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

int calc_0(int x1, int x2, int y1, int y2, bool invert)
{
	if (x1 > x2 || y1 > y2)
		return 0;
	if (invert) {
		swap(x1, y1);
		swap(x2, y2);
	}
	int x = sub(interpolate(x2 + 1, ys_a, dp_a), interpolate(x1, ys_a, dp_a));
	int y = sub(interpolate(y2, ys_b, dp_b), interpolate(y1, ys_b, dp_b));
	return x * y % MOD;
}

int calc(int x1, int x4, int y1, int y4, int n)
{
	if (x1 > x4 || y1 > y4)
		return 0;
	int x2 = (x1 + n - 1) / n;
	int x3 = x4 / n;
	int cnt_x = min(0ll, x3 - x2) / n;

	int y2 = (y1 + n - 1) / n;
	int y3 = y4 / n;
	int cnt_y = min(0ll, y3 - y2) / n;

	if (cnt_x >= 1 && cnt_y >= 1) {
		int full = calc(1, n, 1, n, false);
		int res = full * cnt_x % MOD * cnt_y % MOD;

		res = add(res, calc(x1, x4, y1, y2 - 1, n));
		res = add(res, calc(x1, x4, y3, y4, n));
		res = add(res, calc(x1, x2 - 1, y1, y4, n));
		res = add(res, calc(x3, x4, y1, y4, n));

		res = sub(res, calc(x1, x2 - 1, y1, y2 - 1, n));
		res = sub(res, calc(x1, x2 - 1, y3, y4, n));
		res = sub(res, calc(x3, x4, y1, y2 - 1, n));
		res = sub(res, calc(x3, x4, y3, y4, n));
		return res;
	}
	if (cnt_x >= 1) {
		int res = add(calc(x1, x2 - 1, y1, y4, n), calc(x3 + 1, x4, y1, y4, n));
		return res;
	}
	if (cnt_y >= 1) {
		int res = add(calc(x1, x4, y1, y2 - 1, n), calc(x1, x4, y3 + 1, y4, n));
		return res;
	}
}

void solve()
{
	int n, k, a, b;
	cin >> n >> k >> a >> b;
	tie(ys_a, dp_a) = build_lagrange(a);
	tie(ys_b, dp_b) = build_lagrange(b);

	int x1, x2, y1, y2;
	cin >> x1 >> x2 >> y1 >> y2;
	x1--;
	x2--;
	y1--;
	y2--;
	cout << calc(x1, x2, y1, y2, n) << '\n';
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
