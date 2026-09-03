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
vector<int> multiply(const vector<int> &a, const vector<int> &b)
{
	int need = a.size() + b.size() - 1;
	int sz = 1;
	while (sz < need)
		sz <<= 1;
	vector<int> fa(sz), fb(sz);
	for (int i = 0; i < a.size(); i++)
		fa[i] = a[i];
	for (int i = 0; i < b.size(); i++)
		fb[i] = b[i];
	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < sz; i++)
		fa[i] = fa[i] * fb[i] % MOD;
	fft(fa, true);
	fa.resize(need);
	return fa;
}

void solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<int> a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) {
		if (s[i] == 'V')
			a[i] = 1;
		if (s[i] == 'K')
			b[i] = 1;
	}
	auto rev_a = a, rev_b = b;
	reverse(rev_a.begin(), rev_a.end());
	reverse(rev_b.begin(), rev_b.end());
	auto f = multiply(a, rev_b);
	auto f2 = multiply(rev_a, b);
	vector<bool> possible(n + 1, true);
	for (int i = 1; i < n; i++) {
		possible[i] = (f[n - 1 - i] == 0) && (f2[n - 1 - i] == 0);
	}
	vector<int> res;
	for (int i = 1; i <= n; i++) {
		bool ok = true;
		for (int j = i; j <= n; j += i) {
			if (possible[j])
				continue;

			ok = false;
			break;
		}
		if (ok)
			res.push_back(i);
	}
	cout << res.size() << "\n";
	for (auto x : res)
		cout << x << " ";
	cout << "\n";
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
