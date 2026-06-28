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
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
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
	vector<int> f(n);
	for (int i = 0; i < n; i++) {
		cin >> f[i];
		f[i]--;
	}

	DSU s;
	s.init(n);
	for (int i = 0; i < n; i++) {
		s.unite(i, f[i]);
	}

	int m = s.comps;
	vector<int> roots;
	for (int i = 0; i < n; i++) {
		if (s.find(i) == i)
			roots.push_back(i);
	}
	map<int, int> root_value;
	for (int i = 0; i < m; i++) {
		root_value[roots[i]] = i;
	}

	vector<int> g(n);
	for (int i = 0; i < n; i++) {
		g[i] = root_value[s.find(i)];
	}
	auto h = roots;

	bool is_valid = true;
	for (int i = 0; i < n; i++) {
		if (h[g[i]] != f[i]) {
			is_valid = false;
			break;
		}
	}

	if (!is_valid) {
		cout << -1 << "\n";
		return;
	}

	cout << m << "\n";
	for (int i = 0; i < n; i++) {
		cout << g[i] + 1 << " ";
	}
	cout << "\n";
	for (int i = 0; i < m; i++) {
		cout << h[i] + 1 << " ";
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
