#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 998244353;
const int ROOT = 3;
const int N = 6e5 + 7;

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
	int res = 1;
	while (e) {
		if (e & 1)
			res = res * x % MOD;
		x = x * x % MOD;
		e >>= 1;
	}
	return res;
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
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
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
	int N = a.size() + b.size() - 1;
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
	while (!a.empty() && a.back() == 0)
		a.pop_back();
}

void solve()
{
	int n, k;
	cin >> n >> k;
	map<int, int> freq;
	vector<int> b(k);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		freq[x]++;
	}
	vector<pi> a(freq.begin(), freq.end());
	n = a.size();
	for (int i = 0; i < k; i++)
		cin >> b[i];

	sort(b.begin(), b.end());
	vector<vector<int> > pb(k);
	int i = 0, u = 0, v = 0;
	for (int j = 0; j < k; j++) {
		while (i < n && a[i].fi < b[j]) {
			if (a[i].se >= 2)
				u++;
			if (a[i].se == 1)
				v++;
			i++;
		}
		vector<int> p(2 * u + 1), q(v + 1);
		for (int l = 0; l <= 2 * u; l++)
			p[l] = C(2 * u, l);
		for (int l = 0; l <= v; l++)
			q[l] = C(v, l) * powmod(2, l) % MOD;
		multiply(p, q);
		pb[j] = p;
	}

	int m;
	cin >> m;
	while (m--) {
		int q;
		cin >> q;
		int res = 0;
		for (int i = 0; i < k; i++) {
			int len = q / 2 - b[i] - 1;
			if (len < 0 || len >= (int)pb[i].size())
				continue;
			res = add(res, pb[i][len]);
		}
		cout << res << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
