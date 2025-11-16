#include <bits/stdc++.h>

#define int long long

using namespace std;

struct pt {
	int node, level;

	pt(int node, int level)
	{
		this->node = node;
		this->level = level;
	}
};

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> types(n);
	for (int i = 0; i < n; i++) {
		cin >> types[i];
		types[i]--;
	}
	vector<vector<int> > adj(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<int> dist(k, 0);
	queue<pt> q;
	q.push(pt(0, 0));
	vector<bool> visited(n, false);
	visited[0] = true;
	while (!q.empty()) {
		auto u = q.front().node;
		auto level = q.front().level;
		q.pop();
		dist[types[u]] = level;
		for (auto v : adj[u]) {
			if (visited[v])
				continue;
			visited[v] = true;
			q.push(pt(v, level + 1));
		}
	}
	for (int i = 0; i < k; i++) {
		cout << dist[i] << " ";
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
