#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1001;
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
	for (int i = 0; i < sz; i++) {
		fa[i] = fa[i] * fb[i] % MOD;
	}
	fft(fa, true);
	fa.resize(need);
	for (int i = 0; i < need; i++) {
		fa[i] = fa[i] > 0;
	}
	return fa;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> p(N, 0);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		p[x] = 1;
	}

	vector<int> pk = { 1 };
	while (k) {
		if (k & 1)
			pk = multiply(pk, p);
		p = multiply(p, p);
		k >>= 1;
	}
	n = pk.size();
	for(int i = 0; i < n; i++) {
		if(pk[i]) cout << i << " ";
	}
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
