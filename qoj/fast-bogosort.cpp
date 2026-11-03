#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 998244353;
const int ROOT = 3;
const int N = 1e5 + 7;

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
		for (auto &x : a)
			x = x * mul % MOD;
	}
}

vector<int> multiply(const vector<int> &a, const vector<int> &b)
{
	int n = a.size();
	int m = a.size();

	int N = n + m - 1;
	int sz = 1;
	while (sz < N)
		sz <<= 1;
	vector<int> fa(sz, 0), fb(sz, 0);
	for (int i = 0; i < n; i++)
		fa[i] = a[i];
	for (int i = 0; i < m; i++)
		fb[i] = b[i];
	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < sz; i++)
		fa[i] = fa[i] * fb[i] % MOD;
	fft(fa, true);
	return fa;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> p(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		p[i]--;
	}

	vector<int> fact(n + 1, 0);
	fact[0] = 1;
	for (int i = 1; i <= n; i++)
		fact[i] = fact[i - 1] * i % MOD;
	auto conv_fact = multiply(fact, fact);
	conv_fact.resize(n + 1);

	vector<int> f(n + 1, 0), g(n + 1, 0);
	f[1] = 1;
	g[1] = 0;
	for (int i = 2; i <= n; i++) {
		for (int j = i - 1; j >= 1; j--)
			g[i] = add(g[i], f[j] * add(g[i - j], f[i - j]) % MOD);

		f[i] = sub(fact[i], g[i]);
	}
	vector<int> h(n + 1, 0);
	for (int i = 2; i <= n; i++) {
		int x = 0;
		for (int s = 1; s < i; s++) {
			int y = conv_fact[i - s] * f[s] % MOD * h[s] % MOD;
			x = add(x, y);
		}
		x = add(x, fact[i]);
		x = x * inverse(sub(fact[i], f[i])) % MOD;
	}

	int cnt = 0;
	int start = 0;
	int mx = -1;
	for (int i = 0; i < n; i++) {
		mx = max(mx, p[i]);
		if (mx - start != i - start)
			continue;
		if (i == start) {
			start = i + 1;
			mx = -1;
			continue;
		}
		cnt = add(cnt, h[i - start + 1]);
		start = i + 1;
		mx = -1;
	}
	cout << cnt << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
