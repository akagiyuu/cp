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

void multiply(vector<int> &a, vector<int> &b)
{
	int need = a.size() + b.size() - 1;
	int sz = 1;
	while (sz < need)
		sz <<= 1;
	a.resize(sz);
	b.resize(sz);

	fft(a, false);
	fft(b, false);
	for (int i = 0; i < sz; i++)
		a[i] = a[i] * b[i] % MOD;
	fft(a, true);

	a.resize(need);
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

	multiply(a, b);
	for (auto x : a)
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
