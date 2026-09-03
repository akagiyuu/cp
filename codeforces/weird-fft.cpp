#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 998244353;
const int ROOT = 3;

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

vector<int> mul(int l, int r, const vector<int> &a, const vector<int> &b)

{
	int mid = (l + r) / 2;
	int need = r - l - 1;
	int sz = 1;
	while (sz < need)
		sz <<= 1;

	vector<int> fa(sz), fb(sz);
	for (int i = 0; i < mid - l; i++)
		fa[i] = a[i + l];
	for (int i = 0; i < r - mid; i++)
		fb[i] = b[i + mid];

	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < sz; i++)
		fa[i] = fa[i] * fb[i] % MOD;
	fft(fa, true);
	fa.resize(need);

	return fa;
}

void calc(int l, int r, const vector<int> &a, const vector<int> &b, vector<int> &res)

{
	if (r - l <= 1)
		return;
	int mid = (l + r) / 2;
	calc(l, mid, a, b, res);
	calc(mid, r, a, b, res);
	auto c = mul(l, r, a, b);
	int offset = l + mid;

	int n = c.size();
	for (int i = 0; i < n; i++) {
		res[i + offset] += c[i];
	}
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int m;
	cin >> m;
	vector<int> b(m);
	for (int i = 0; i < m; i++)
		cin >> b[i];

	int sz = max(a.size(), b.size());
	a.resize(sz, 0);
	b.resize(sz, 0);
	vector<int> res(2 * sz - 1, 0);
	calc(0, sz, a, b, res);
	res.resize(n + m - 1);
	for (auto x : res)
		cout << x << " ";
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
