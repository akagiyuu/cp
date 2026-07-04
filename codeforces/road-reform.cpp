#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

struct DSU {
	int n;
	vector<int> parent, sz;
	int comps;

	void init(int _n)
	{
		n = _n;
		parent.resize(n);
		sz.assign(n, 1);
		for (int i = 0; i < n; i++)
			parent[i] = i;
		comps = n;
	}

	int find(int x) const
	{
		while (parent[x] != x)
			x = parent[x];
		return x;
	}

	bool unite(int a, int b)
	{
		a = find(a);
		b = find(b);
		if (a == b)
			return false;
		if (sz[a] > sz[b])
			swap(a, b);
		parent[a] = b;
		sz[b] += sz[a];
		--comps;
		return true;
	}
};

struct Edge {
	int u;
	int v;
	int w;
	bool operator<(const Edge &other) const
	{
		return w < other.w;
	}
};

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<Edge> a(m);
	for (int i = 0; i < m; i++) {
		cin >> a[i].u >> a[i].v >> a[i].w;
		a[i].u--;
		a[i].v--;
	}
	sort(a.begin(), a.end());

	int res = LLONG_MAX;
	DSU s;

	int i = 0;
	while (i < m && a[i].w <= k)
		i++;
	s.init(n);
	for (int j = 0; j < i; j++) {
		s.unite(a[j].u, a[j].v);
	}

	if (s.comps == 1) {
		res = min(res, k - a[i - 1].w);
		if (i < m)
			res = min(res, a[i].w - k);
	} else {
		int cur = 0;
		for (int j = i; j < m; j++) {
			if (s.unite(a[j].u, a[j].v)) {
				cur += a[j].w - k;
			}
		}
		res = min(res, cur);
	}
	cout << res << "\n";
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
