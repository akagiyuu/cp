#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 1000000007;

bool check(int u, int p, vector<bool> &visited, const vector<vector<int> > &adj, const vector<int> &c)
{
	if (p != -1 && c[u] != c[p])
		return false;
	visited[u] = true;
	for (auto v : adj[u]) {
		if (visited[v])
			continue;
		if (!check(v, u, visited, adj, c)) {
			return false;
		}
	}
	return true;
}

void solve()
{
	int n;
	cin >> n;
	vector<pi> edges;
	vector<vector<int> > adj(n);
	vector<int> c(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
		edges.push_back({ u, v });
	}
	for (int i = 0; i < n; i++)
		cin >> c[i];
	for (auto [u, v] : edges) {
		if (c[u] == c[v])
			continue;
		vector<bool> visisted(n, false);
		visisted[u] = true;
		bool ok = true;
		for (auto x : adj[u]) {
			ok = check(x, -1, visisted, adj, c);
			if (!ok)
				break;
		}
		if (ok) {
			cout << "YES\n";
			cout << u + 1 << "\n";
			return;
		}

		visisted.assign(n, false);
		visisted[v] = true;
		ok = true;
		for (auto x : adj[v]) {
			ok = check(x, -1, visisted, adj, c);
			if (!ok)
				break;
		}
		if (ok) {
			cout << "YES\n";
			cout << v + 1 << "\n";
			return;
		}
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	cout << 1 << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
