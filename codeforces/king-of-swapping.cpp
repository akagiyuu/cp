#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

vector<bool> visited;

void dfs(int v, vector<vector<int> > const &adj, vector<int> &output)
{
	visited[v] = true;
	for (auto u : adj[v]) {
		if (visited[u])
			continue;
		dfs(u, adj, output);
	}
	output.push_back(v);
}

void scc(vector<vector<int> > const &adj, vector<vector<int> > &comps)
{
	int n = adj.size();
	comps.clear();

	vector<int> order;

	visited.assign(n, false);

	for (int i = 0; i < n; i++) {
		if (visited[i])
			continue;
		dfs(i, adj, order);
	}

	vector<vector<int> > adj_rev(n);
	for (int v = 0; v < n; v++) {
		for (auto u : adj[v]) {
			adj_rev[u].push_back(v);
		}
	}

	visited.assign(n, false);
	reverse(order.begin(), order.end());

	vector<int> roots(n, 0);

	for (auto v : order)
		if (!visited[v]) {
			std::vector<int> component;
			dfs(v, adj_rev, component);
			comps.push_back(component);
			int root = *component.begin();
			for (auto u : component)
				roots[u] = root;
		}
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int> > adj(n), comps;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
	}
	scc(adj, comps);
	if (comps.size() == 1) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
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
