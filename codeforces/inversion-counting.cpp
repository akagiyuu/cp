#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 998244353;
const int ROOT = 3;
const int LIM = 1.6e4 + 100;

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

vector<int> root, inv_root, rev;
void init_fft(int n)
{
	int lg = __builtin_ctz(n);
	root.resize(lg + 1);
	inv_root.resize(lg + 1);
	rev.resize(n);
	for (int i = 1; i <= lg; i++) {
		root[i] = powmod(ROOT, (MOD - 1) / (1ll << i));
		inv_root[i] = inverse(root[i]);
	}
	for (int i = 1; i < n; ++i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
}

void fft(vector<int> &a, bool invert)
{
	int n = a.size();
	assert((n & (n - 1)) == 0);
	for (int i = 0; i < n; ++i) {
		int j = rev[i];
		if (i < j)
			swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len *= 2) {
		int wlen = invert ? inv_root[__builtin_ctz(len)] : root[__builtin_ctz(len)];
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

void brute_forces(int l, int r, const vector<int> &a, vector<int> &res)
{
	for (int i = l; i < r; i++) {
		for (int j = i + 1; j < r; j++) {
			if (a[i] < a[j])
				continue;
			res[a[i] - a[j]]++;
		}
	}
}

vector<int> L, R;
void cdq_fft(int l, int r, const vector<int> &a, vector<int> &res)
{
	if (r - l <= LIM)
		return brute_forces(l, r, a, res);
	int n = a.size();
	int mid = (l + r) / 2;
	cdq_fft(l, mid, a, res);
	cdq_fft(mid, r, a, res);

	int N = 2 * n - 1;
	int sz = 1;
	while (sz < N)
		sz <<= 1;
	L.assign(sz, 0);
	R.assign(sz, 0);
	for (int i = l; i < mid; i++)
		L[a[i]]++;
	for (int i = mid; i < r; i++)
		R[n - 1 - a[i]]++;
	fft(L, false);
	fft(R, false);
	for (int i = 0; i < sz; i++) {
		L[i] = L[i] * R[i] % MOD;
	}
	fft(L, true);
	for (int k = 1; k < n; k++) {
		res[k] = add(res[k], L[n - 1 + k]);
	}
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		b[i] = i;
	sort(b.begin(), b.end(), [&a](int i, int j) { return a[i] < a[j]; });

	int sz = 1;
	int N = 2 * n - 1;
	while (sz < N)
		sz <<= 1;
	init_fft(sz);
	vector<int> res(n, 0);
	cdq_fft(0, n, b, res);
	for (int k = 1; k < n; k++)
		cout << res[k] << ' ';
	cout << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
