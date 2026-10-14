#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 998244353;
const int N = 507;
const int ROOT = 3;

int c[N][N + 1];

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

void fft(vector<int> &a, bool invert)
{
	int n = a.size();
	assert((n & (n - 1)) == 0);
	int lg = __builtin_ctz(n);
	for (int i = 0; i < n; ++i) {
		int j = 0;
		for (int k = 0; k < lg; ++k)
			if ((i & 1 << k) != 0)
				j |= 1ll << (lg - k - 1);
		if (i < j)
			swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len *= 2) {
		int wlen = powmod(ROOT, (MOD - 1) / len);
		if (invert)
			wlen = inverse(wlen);
		for (int i = 0; i < n; i += len) {
			int w = 1;
			for (int j = 0; j < len / 2; ++j) {
				int u = a[i + j];
				int v = a[i + j + len / 2] * w % MOD;
				a[i + j] = add(u, v);
				a[i + j + len / 2] = sub(u, v);
				w = w * wlen % MOD;
			}
		}
	}
	if (invert) {
		int mul = inverse(n);
		for (int i = 0; i < n; i++)
			a[i] = a[i] * mul % MOD;
	}
}
vector<int> multiply(const vector<int> &a, const vector<int> &b, int need)
{
	int N = a.size() + b.size() - 1;
	int sz = 1;
	while (sz < N)
		sz <<= 1;
	vector<int> fa(sz), fb(sz);
	for (int i = 0; i < (int)a.size(); i++)
		fa[i] = a[i];
	for (int i = 0; i < (int)b.size(); i++)
		fb[i] = b[i];
	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < sz; i++) {
		fa[i] = fa[i] * fb[i] % MOD;
	}
	fft(fa, true);
	fa.resize(need);
	return fa;
}

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
	if (k < 0 || k > n)
		return 0;
	return c[n][k];
}

int calc(int i, vector<int> &ks, int s, int n, int m, const vector<int> &f)
{
	if (i == n - 1) {
		ks[i] = s;
		int res = 1;
		for (auto k : ks) {
			res = res * f[k] % MOD;
		}
		return res;
	}
	int res = 0;
	for (int k = 0; k <= s; k += 2) {
		ks[i] = k;
		res = add(res, calc(i + 1, ks, s - k, n, m, f));
		ks[i] = 0;
	}
	return res;
}

int solve()
{
	int n, m;
	cin >> n >> m;

	vector<vector<int> > dp0(m / 2 + 1, vector<int>(m + 1, 0));
	dp0[0][1] = 1;
	for (int k = 1; k <= m / 2; k++) {
		for (int y = 2 * k; y <= m; y++) {
			for (int x = 1; x <= y - 1; x++) {
				dp0[k][y] = add(dp0[k][y], dp0[k - 1][x]);
			}
		}
	}
	vector<int> f(m + 1, 0);
	for (int k = 0; k <= m; k += 2) {
		for (int x = 1; x <= m; x++) {
			f[k] = add(f[k], dp0[m / 2 - k / 2][x]);
		}
	}
	vector<int> fn = { 1 };
	int e = n - 1;
	while (e) {
		if (e & 1)
			fn = multiply(fn, f, m + 1);
		f = multiply(f, f, m + 1);
		e >>= 1;
	}

	vector<int> dps(m + 1);
	for (int s = 0; s <= m; s += 2) {
		vector<vector<int> > dp((m - s) / 2 + 1, vector<int>(m + 1, 0));
		if (s == 0) {
			dp[0][1] = 1;
		} else {
			for (int x = 1; x <= m; x++) {
				dp[0][x] = C(x - 1, s - 1);
			}
		}
		for (int x = 2; x <= m; x++)
			dp[0][x] = add(dp[0][x], dp[0][x - 1]);
		for (int k = 1; k <= (m - s) / 2; k++) {
			for (int y = 2 * k + s; y <= m; y++) {
				dp[k][y] = add(dp[k][y], dp[k - 1][y - 1]);
			}
			if (k < (m - s) / 2) {
				for (int x = 2; x <= m; x++)
					dp[k][x] = add(dp[k][x], dp[k][x - 1]);
			}
		}
		dps[s] = dp[(m - s) / 2][m];
	}
	if (n == 1)
		return dps[0];
	int res = 0;
	for (int s = 0; s <= m; s += 2) {
		res = add(res, dps[s] * fn[s] % MOD);
	}
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	cout << solve() << '\n';
}
