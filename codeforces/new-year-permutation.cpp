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
		for (int i = 0; i < n; i++)
			parent[i] = i;
		sz.assign(n, 1);
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

DSU s;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	s.init(n);
	for (int i = 0; i < n; i++) {
		string tmp;
		cin >> tmp;
		for (int j = 0; j < n; j++) {
			if (tmp[j] == '1')
				s.unite(i, j);
		}
	}
	vector<vector<int> > comps(n);
	vector<vector<int> > comps_val(n);
	for (int i = 0; i < n; i++) {
		comps[s.find(i)].push_back(i);
		comps_val[s.find(i)].push_back(a[i]);
	}

	vector<int> res(n);
	for (int i = 0; i < n; i++) {
		if (comps[i].empty())
			continue;
		sort(comps_val[i].begin(), comps_val[i].end());
		int m = comps[i].size();
		for (int j = 0; j < m; j++) {
			res[comps[i][j]] = comps_val[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		cout << res[i] << " ";
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
