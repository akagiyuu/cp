#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

bool dfs(int u, vector<int> &p, int s, vector<bool> &in_path, const vector<vector<int> > &adj,
	 const vector<vector<bool> > &is_adj)
{
	in_path[u] = true;
	if (p.size() >= 3 && is_adj[u][s]) {
		return true;
	}
	for (auto v : adj[u]) {
		if (in_path[v])
			continue;
		p.push_back(v);
		if (dfs(v, p, s, in_path, adj, is_adj)) {
			return true;
		}
		p.pop_back();
	}
	in_path[u] = false;
	return false;
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int> > adj(n);
	vector<vector<bool> > is_adj(n, vector<bool>(n, false));
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
		is_adj[u][v] = is_adj[v][u] = true;
	}

	for (int u = 0; u < n; u++) {
		if (adj[u].size() < 4)
			continue;
		vector<bool> in_path(n, false);
		vector<int> path = { u };
		if (!dfs(u, path, u, in_path, adj, is_adj))
			continue;
		path.push_back(u);

		cout << "YES\n";
		int m = path.size();
		cout << m + 1 << "\n";
		for (int i = 0; i < m - 1; i++) {
			cout << path[i] + 1 << " " << path[i + 1] + 1 << "\n";
		}
		int cnt = 0;
		for (auto v : adj[u]) {
			if (in_path[v])
				continue;
			cnt++;
			cout << u + 1 << " " << v + 1 << "\n";
			if (cnt == 2)
				break;
		}
		return;
	}
	cout << "NO\n";
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
