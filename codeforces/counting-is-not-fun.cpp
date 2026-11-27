#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define ii pair<int, int>
#define fi first
#define se second

const int MOD = 998244353;
const int N = 1e6 + 7;

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
void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % MOD;
	ifact[N - 1] = inverse(fact[N - 1]);
	for (int i = N - 2; i >= 0; i--)
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}
int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * ifact[n - k] % MOD * ifact[k] % MOD;
}
int f(int x)
{
	assert(x % 2 == 0);
	x /= 2;
	return C(2 * x, x) * inverse(x + 1) % MOD;
}

void solve()
{
	int n;
	cin >> n;
	vector<ii> g(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> g[i].fi >> g[i].se;
	g[0] = { 0, 2 * n + 1 };

	vector<int> sz(n + 1, 0);
	for (int i = 0; i <= n; i++)
		sz[i] = g[i].se - g[i].fi - 1;

	vector<int> par(n + 1, 0);
	vector<vector<int> > children(n + 1);
	int res = f(sz[0]);
	cout << res << ' ';

	for (int i = 1; i <= n; i++) {
		int p = 0;
		bool quit = false;
		while (!quit) {
			quit = true;
			for (auto c : children[p]) {
				if (g[c].fi < g[i].fi && g[i].se < g[c].se) {
					p = c;
					quit = false;
					break;
				}
			}
		}

		int sz_p = sz[p];
		auto tmp = children[p];

		children[p].clear();
		children[p].push_back(i);
		par[i] = p;
		sz[p] = g[p].se - g[p].fi - 1 - (g[i].se - g[i].fi + 1);
		for (auto c : tmp) {
			if (g[i].fi < g[c].fi && g[c].se < g[i].se) {
				par[c] = i;
				children[i].push_back(c);
				sz[i] -= g[c].se - g[c].fi + 1;
			} else {
				par[c] = p;
				children[p].push_back(c);
				sz[p] -= g[c].se - g[c].fi + 1;
			}
		}
		res = res * inverse(f(sz_p)) % MOD * f(sz[p]) % MOD;
		res = res * f(sz[i]) % MOD;
		cout << res << ' ';
	}
	cout << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	int t;
	cin >> t;
	while (t--)
		solve();
}
