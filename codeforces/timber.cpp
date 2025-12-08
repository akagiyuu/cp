#include <bits/stdc++.h>

using namespace std;

const int N = 1e6;
const int MOD = 998244353;
const int ROOT = 3;

static inline int add(int a, int b)
{
	a += b;
	return a < MOD ? a : a - MOD;
}
static inline int sub(int a, int b)
{
	a -= b;
	return a < 0 ? a + MOD : a;
}
static inline int mul(int a, int b)
{
	return (long long)a * (long long)b % MOD;
}
static inline int powmod(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1)
			res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}
static inline int inv(int a)
{
	return powmod(a, MOD - 2);
}
struct FFT {
	int n;
	vector<int> root_pw;
	vector<int> inv_root_pw;
	FFT(int n)
		: n(n)
		, root_pw(n + 1)
		, inv_root_pw(n + 1)
	{
		for (int len = 2; len <= n; len <<= 1) {
			root_pw[len] = powmod(ROOT, (MOD - 1) / len);
			inv_root_pw[len] = inv(root_pw[len]);
		}
	}

	void fft(vector<int> &a, bool invert)
	{
		assert((n & (n - 1)) == 0);
		int lg = __builtin_ctz(n);
		for (int i = 0; i < n; i++) {
			int j = 0;
			for (int k = 0; k < lg; k++)
				if ((i & 1 << k) != 0)
					j |= 1 << (lg - k - 1);
			if (i < j)
				swap(a[i], a[j]);
		}
		for (int len = 2; len <= n; len *= 2) {
			int wlen = root_pw[len];
			if (invert)
				wlen = inv_root_pw[len];
			for (int i = 0; i < n; i += len) {
				int w = 1;
				for (int j = 0; j < len / 2; j++) {
					int u = a[i + j];
					int v = mul(a[i + j + len / 2], w);
					a[i + j] = add(u, v);
					a[i + j + len / 2] = sub(u, v);
					w = mul(w, wlen);
				}
			}
		}
		if (invert) {
			int inv_n = inv(n);
			for (auto &x : a)
				x = mul(x, inv_n);
		}
	}
};

int fact[N], ifact[N];
void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = mul(fact[i - 1], i);
	}
	ifact[N - 1] = inv(fact[N - 1]);
	for (int i = N - 2; i >= 0; i--) {
		ifact[i] = mul(ifact[i + 1], i + 1);
	}
}
int C(int n, int k)
{
	if (k < 0 || n < k)
		return 0;
	return mul(fact[n], mul(ifact[k], ifact[n - k]));
}

int solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	long long offset = (long long)m * (k + 1);
	if (n < offset)
		return 0;
	if (n <= 0)
		return 0;
	n = n - offset + 1;
	if (n <= 0)
		return 0;
	int N = 1;
	int full = 2 * n - 1;
	while (N < full)
		N <<= 1;

	vector<int> dp(N, 0);
	for (int i = 0; i < n; i++) {
		dp[i] = 1;
	}
	vector<int> t(N, 0);

	vector<int> denom(N);
	for (int i = 0; i < n; i++) {
		denom[i] = C(m - 1 + i, i);
	}

	int c = powmod(2, m);
	if (min(k, n) == n) {
		for (int i = 0; i < n; i++) {
			if (i % n != 0)
				continue;
			int j = i / n;
			t[i] = mul(C(m, j), c);
		}
	} else {
		int inv2 = inv(2);
		int cur = 1;
		for (int b = 0; b <= m; b++) {
			int j = b * k;
			if (j >= n)
				break;
			t[j] = mul(c, mul(C(m, b), cur));
			if (b & 1)
				t[j] = sub(0, t[j]);
			cur = mul(cur, inv2);
		}
	}

	FFT f(N);
	f.fft(t, false);
	f.fft(denom, false);
	f.fft(dp, false);
	for (int i = 0; i < N; i++) {
		dp[i] = mul(dp[i], mul(t[i], denom[i]));
	}
	f.fft(dp, true);

	return dp[n - 1];
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	cout << solve() << "\n";
}
