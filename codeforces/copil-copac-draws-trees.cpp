#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	map<pi, int> edges;
	vector<vector<int> > adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		if (u > v)
			swap(u, v);
		edges[{ u, v }] = i;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	auto get_edges = [edges](int u, int v) {
		if (u > v)
			swap(u, v);
		auto it = edges.find({ u, v });
		return it == edges.end() ? -1 : it->se;
	};

	vector<int> cost(n, -1);
	queue<int> q;
	vector<bool> visisted(n, false);
	vector<int> p(n, -1);
	cost[0] = 0;
	visisted[0] = true;
	for (auto v : adj[0]) {
		cost[v] = 1;
		visisted[v] = true;
		q.push(v);
		p[v] = 0;
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		int x = p[u];
		for (auto v : adj[u]) {
			if (visisted[v])
				continue;
			cost[v] = cost[u];
			if (get_edges(x, u) >= get_edges(u, v))
				cost[v]++;
			p[v] = u;
			visisted[v] = true;
			q.push(v);
		}
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
		res = max(res, cost[i]);
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
