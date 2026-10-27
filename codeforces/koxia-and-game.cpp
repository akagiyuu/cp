#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;

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

struct DSU {
	int n;
	vector<int> sz, parent, edge_cnt;
	vector<bool> has_loop;

	DSU(int _n)
	{
		n = _n;
		sz.assign(n, 1);
		parent.resize(n);
		edge_cnt.assign(n, 0);
		has_loop.assign(n, false);

		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	int find(int x)
	{
		if (parent[x] == x)
			return x;
		return parent[x] = find(parent[x]);
	}

	void unite(int x, int y)
	{
		bool self_loop = (x == y);

		x = find(x);
		y = find(y);

		if (x == y) {
			edge_cnt[x]++;
			if (self_loop)
				has_loop[x] = 1;
			return;
		}

		if (sz[x] < sz[y])
			swap(x, y);

		sz[x] += sz[y];
		edge_cnt[x] += edge_cnt[y] + 1;
		has_loop[x] = has_loop[x] || has_loop[y];
		parent[y] = x;
	}
};

int solve()
{
	int n;
	cin >> n;

	vector<int> a(n), b(n);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
	}

	for (int i = 0; i < n; i++) {
		cin >> b[i];
		b[i]--;
	}

	DSU s(n);

	for (int i = 0; i < n; i++)
		s.unite(a[i], b[i]);

	int res = 1;

	for (int i = 0; i < n; i++) {
		int p = s.find(i);

		if (p != i)
			continue;

		if (s.sz[p] != s.edge_cnt[p])
			return 0;

		if (s.has_loop[p])
			res = res * n % MOD;
		else
			res = res * 2 % MOD;
	}

	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin >> t;

	while (t--)
		cout << solve() << '\n';
}
