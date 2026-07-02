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

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
	}
	DSU s;
	s.init(n);
	for (int i = 0; i < n; i++) {
		s.unite(i, a[i]);
	}

	int max_comps = 0;
	for (int i = 0; i < n - 1; i++) {
		if (s.find(a[i]) != s.find(a[i + 1]))
			max_comps = max(max_comps, s.comps - 1);
		else
			max_comps = max(max_comps, s.comps + 1);
	}
	cout << n - max_comps << "\n";
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
