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
int inv(int x)
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
			wlen = inv(wlen);
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
		int mul = inv(n);
		for (auto &x : a)
			x = x * mul % MOD;
	}
}
inline void norm(vector<int> &a)
{
	while (!a.empty() && a.back() == 0)
		a.pop_back();
}
vector<int> multiply(vector<int> a, vector<int> b, int need)
{
	int n = a.size() + b.size() - 1;
	int sz = 1;
	while (sz < n)
		sz <<= 1;
	a.resize(sz, 0);
	b.resize(sz, 0);
	fft(a, false);
	fft(b, false);
	for (int i = 0; i < sz; i++)
		a[i] = a[i] * b[i] % MOD;
	fft(a, true);
	a.resize(need, 0);
	return a;
}
vector<int> invert(vector<int> a, int n)
{
	norm(a);
	assert(!a.empty() && a[0] != 0);
	vector<int> r = { inv(a[0]) };
	int cur = 1;
	while (cur < n) {
		int need = min(cur * 2, n);
		auto pr = multiply(a, r, need);
		for (int i = 0; i < need; i++)
			pr[i] = sub(0, pr[i]);
		pr[0] = add(pr[0], 2);
		r = multiply(r, pr, need);
		norm(r);
		cur = need;
	}
	r.resize(n);
	norm(r);
	return r;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> c(n), r(n);
	for (int i = 0; i < n; i++)
		cin >> c[i];
	for (int i = 0; i < n; i++)
		cin >> r[i];

	r[0] = r[0] * 2 % MOD;
	for (int i = 0; i < n; i++)
		r[i] = sub(0, r[i]);
	r[0] = add(r[0], 1);

	r = invert(r, n);
	auto res = multiply(c, r, n);
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
