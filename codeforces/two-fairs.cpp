#include <bits/stdc++.h>

using namespace std;

#define int long long

int n, m, a, b;
vector<vector<int> > adj;
vector<bool> visited;

void dfs(int u)
{
	if (visited[u])
		return;
	visited[u] = true;
	for (auto v : adj[u]) {
		if (visited[v])
			continue;
		dfs(v);
	}
}

void solve()
{
	cin >> n >> m >> a >> b;
	a--;
	b--;
	adj.assign(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	visited.assign(n, false);
	visited[a] = true;
	dfs(b);
	int x = 0;
	for (int i = 0; i < n; i++)
		x += !visited[i];

	visited.assign(n, false);
	visited[b] = true;
	dfs(a);
	int y = 0;
	for (int i = 0; i < n; i++)
		y += !visited[i];
	cout << x * y << '\n';
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
