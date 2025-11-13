#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 998244353;

vector<int> build_grundy(const vector<int> &p)
{
	int n = p.size() - 1;
	vector<int> mx(n + 1, -1), g(n + 1, 0);
	mx[0] = 0;

	for (int i = 1; i <= n; i++) {
		for (int x = 0; x <= n; x++) {
			if (mx[x] < max(i - p[i], 0ll)) {
				g[i] = x;
				mx[x] = i;
				break;
			}
		}
	}

	return g;
}

int binpow(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

int inv(int a)
{
	return binpow(a, MOD - 2);
}

int add(int a, int b)
{
	int res = a + b;
	if (res < MOD)
		return res;
	return res - MOD;
}

int sub(int a, int b)
{
	int res = a - b;
	if (res < 0)
		return res + MOD;
	return res;
}

void fwht(vector<int> &a, bool inverse = false)
{
	int n = a.size();
	for (int len = 1; len < n; len <<= 1) {
		for (int i = 0; i < n; i += (len << 1)) {
			for (int j = 0; j < len; j++) {
				int u = a[i + j];
				int v = a[i + j + len];
				int x = add(u, v);
				int y = sub(u, v);
				a[i + j] = x;
				a[i + j + len] = y;
			}
		}
	}
	if (inverse) {
		int inv_n = inv(n);
		for (int i = 0; i < n; i++)
			a[i] = (a[i] * inv_n) % MOD;
	}
}

void solve()
{
	int n, k, r;
	cin >> n >> k >> r;
	vector<int> p(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}

	auto g = build_grundy(p);
	int max_g = 0;
	for (auto x : g)
		max_g = max(max_g, x);
	int m = 1;
	while (m <= max_g)
		m <<= 1;
	vector<int> a(m, 0), b(m, 0);
	for (int i = 0; i <= n; i++) {
		int x = g[i];
		a[x] = add(a[x], 1);
		if (i + k > n || g[i] == g[i + k])
			b[x] = add(b[x], 1);
	}
	fwht(a);
	fwht(b);
	for (int i = 0; i < m; i++) {
		a[i] = binpow(a[i], r);
		b[i] = binpow(b[i], r);
	}
	fwht(a, true);
	fwht(b, true);
	cout << (a[0] - b[0] + MOD) % MOD << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
