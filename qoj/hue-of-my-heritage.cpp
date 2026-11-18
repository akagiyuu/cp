#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;

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

void solve()
{
	int n;
	cin >> n;
	vector<vector<int> > children(n + 1);
	vector<int> parent(n + 1);
	vector<int> d(n + 1, 0);
	vector<vector<int> > depth_nodes(n);
	depth_nodes[0].push_back(1);
	int max_d = 0;
	for (int i = 2; i <= n; i++) {
		int p;
		cin >> p;
		children[p].push_back(i);
		parent[i] = p;
		d[i] = d[p] + 1;
		depth_nodes[d[i]].push_back(i);
		max_d = max(max_d, d[i]);
	}

	int p = inverse(2);

	int res = max_d + 1;
	for (int d = 1; d <= max_d; d++) {
		vector<int> f(n + 1, 1);

		for (int u : depth_nodes[d - 1])
			f[u] = powmod(p, children[u].size());

		for (int k = d - 1; k >= 1; k--) {
			for (int u : depth_nodes[k]) {
				f[parent[u]] = f[parent[u]] * p % MOD * add(1, f[u]) % MOD;
			}
		}
		res = sub(res, f[1]);
	}
	cout << res << '\n';
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
