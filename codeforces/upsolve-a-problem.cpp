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

void multiply(vector<int> &a, vector<int> b)
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
}
void cdq_fft(int left, int right, vector<int> &dp, const vector<int> &c, const vector<int> &r)
{
	if (left >= right)
		return;
	if (left + 1 == right) {
		dp[left] = add(dp[left], c[left]);
		return;
	}

	int mid = (left + right) / 2;
	cdq_fft(left, mid, dp, c, r);
	vector<int> p(mid - left);
	for (int i = left; i < mid; i++)
		p[i - left] = dp[i];
	multiply(p, r);
	for (int i = mid; i < right; i++) {
		dp[i] = add(dp[i], p[i - left]);
	}
	cdq_fft(mid, right, dp, c, r);
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
	vector<int> dp(n, 0);
	cdq_fft(0, n, dp, c, r);
	for (auto x : dp)
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
