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
int powmod(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % MOD;
		}
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
int inverse(int n)
{
	return powmod(n, MOD - 2);
}

void fft(vector<int> &a, bool invert)
{
	int n = a.size();
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
	int sz = 1;
	while (sz < a.size() + b.size())
		sz <<= 1;
	vector<int> fa(sz), fb(sz);
	for (int i = 0; i < a.size(); i++)
		fa[i] = a[i];
	for (int i = 0; i < b.size(); i++)
		fb[i] = b[i];
	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < sz; i++) {
		fa[i] = fa[i] * fb[i] % MOD;
	}
	fft(fa, true);

	int n = a.size() / 2;;
	vector<int> res(a.size());
	for (int i = 0; i < a.size(); i++) {
		res[i] = fa[i + n] > 0;
	}
	return res;
}

bool solve()
{
	int n, m;
	cin >> n >> m;
	int b = m / n;
	m -= b * n;
	vector<int> p(2 * n + 1);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		p[x - b + n] = 1;
	}

	vector<int> pn(2 * n + 1);
	pn[n] = 1;
	int e = n;
	while (e > 0) {
		if (e & 1)
			pn = multiply(pn, p);
		p = multiply(p, p);
		e >>= 1;
	}

	return pn[m + n] > 0;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		if (solve())
			cout << "Yes\n";
		else
			cout << "No\n";
	}
}
