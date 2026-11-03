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

void multiply(vector<int> &a, vector<int> &b)
{
	int n = a.size();
	int m = b.size();

	int N = n + m - 1;
	int sz = 1;
	while (sz < N)
		sz <<= 1;
	a.resize(sz);
	b.resize(sz);
	fft(a, false);
	fft(b, false);
	for (int i = 0; i < sz; i++)
		a[i] = a[i] * b[i] % MOD;
	fft(a, true);
}

void cdq_g(int l, int r, vector<int> &g, const vector<int> &fact, const vector<int> &conv_fact)
{
	if (l >= r)
		return;
	if (l == r - 1) {
		g[l] = add(g[l], sub(conv_fact[l], 2 * fact[l] % MOD));
		return;
	}
	int mid = (l + r) / 2;

	cdq_g(l, mid, g, fact, conv_fact);

	vector<int> p(g.begin() + l, g.begin() + mid);
	vector<int> fact_clone(fact.begin(), fact.begin() + (r - l));
	multiply(p, fact_clone);

	for (int i = mid; i < r; i++)
		g[i] = sub(g[i], p[i - l]);

	cdq_g(mid, r, g, fact, conv_fact);
}

void cdq_f(int l, int r, vector<int> &f, const vector<int> &fact, const vector<int> &conv_fact, const vector<int> &g)
{
	if (l >= r)
		return;
	if (l == r - 1) {
		f[l] = add(f[l], fact[l]) * inverse(g[l]) % MOD;
		return;
	}

	int mid = (l + r) / 2;

	cdq_f(l, mid, f, fact, conv_fact, g);

	vector<int> p(mid - l);
	for (int i = l; i < mid; i++)
		p[i - l] = sub(fact[i], g[i]) * f[i] % MOD;
	vector<int> conv_fact_clone(conv_fact.begin(), conv_fact.begin() + (r - l));
	multiply(p, conv_fact_clone);

	for (int i = mid; i < r; i++)
		f[i] = add(f[i], p[i - l]);

	cdq_f(mid, r, f, fact, conv_fact, g);
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
	auto conv_fact = fact, tmp = fact;
	multiply(conv_fact, tmp);

	vector<int> g(n + 1, 0);
	cdq_g(2, n + 1, g, fact, conv_fact);
	// for (int i = 2; i <= n; i++) {
	// 	g[i] = sub(conv_fact[i], 2 * fact[i] % MOD);
	// 	for (int j = 0; j <= i - 1; j++)
	// 		g[i] = sub(g[i], g[j] * fact[i - j] % MOD);
	// }

	vector<int> f(n + 1, 0);
	cdq_f(2, n + 1, f, fact, conv_fact, g);
	// for (int i = 2; i <= n; i++) {
	// 	int x = 0;
	// 	for (int s = 0; s <= i - 1; s++) {
	// 		int y = conv_fact[i - s] * sub(fact[s], g[s]) % MOD * f[s] % MOD;
	// 		x = add(x, y);
	// 	}
	// 	x = add(x, fact[i]);
	// 	x = x * inverse(g[i]) % MOD;
	// 	f[i] = x;
	// }

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
		cnt = add(cnt, f[i - start + 1]);
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
