#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

struct DSU {
	int n, comps;
	vector<int> parent, sz;

	DSU(int _n)
	{
		n = _n;
		comps = n;
		parent.resize(n);
		for (int i = 0; i < n; i++)
			parent[i] = i;
		sz.assign(n, 1);
	}

	int find(int x)
	{
		if (parent[x] == x)
			return x;
		return parent[x] = find(parent[x]);
	}

	bool unite(int a, int b)
	{
		a = find(a), b = find(b);
		if (a == b) {
			return false;
		}
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
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> c(n);
	for (int i = 0; i < n; i++) {
		cin >> c[i];
		c[i]--;
	}

	DSU s(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		s.unite(u, v);
	}

	unordered_map<int, vector<int> > comps;

	for (int u = 0; u < n; u++) {
		int r = s.find(u);
		comps[r].push_back(u);
	}

	vector<int> max_cnt(n, 0), sum_cnt(n, 0);
	unordered_map<int, int> cnt;
	for (auto [r, g] : comps) {
		cnt.clear();
		for (auto u : g) {
			cnt[c[u]]++;
			max_cnt[r] = max(max_cnt[r], cnt[c[u]]);
			sum_cnt[r]++;
		}
	}

	int res = 0;
	for (int u = 0; u < n; u++) {
		res += sum_cnt[u] - max_cnt[u];
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
