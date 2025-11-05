#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

int calc_size(int u, vector<bool> &visited, vector<vector<int> > &adj, vector<int> &size)
{
	if (size[u] != 0)
		return size[u];
	size[u] = 1;
	visited[u] = true;
	for (auto v : adj[u]) {
		if (visited[v])
			continue;
		size[u] = (size[u] + calc_size(v, visited, adj, size));
	}
	return size[u];
}

void solve()
{
	int n, u, v;
	cin >> n;

	vector<vector<int> > adj(n);
	for (int i = 0; i < n - 1; i++) {
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<int> size(n, 0);
	vector<bool> visited(n, false);
	calc_size(n - 1, visited, adj, size);

	for (int i = 0; i < n; i++) {
		size[i] = (n - size[i]) * size[i];
	}
	size.pop_back();
	n--;
	sort(size.begin(), size.end());
	for (int i = 0; i < n; i++) {
		size[i] %= MOD;
	}

	int m;
	cin >> m;
	vector<int> pr(m);
	for (int i = 0; i < m; i++) {
		cin >> pr[i];
	}

	sort(pr.begin(), pr.end());
	int res = 0;
	while (m > n) {
		pr[m - 2] = (pr[m - 2] * pr[m - 1]) % MOD;
		m--;
	}

	int j = 0;
	for (int i = max(n - m, 0ll); i < n; i++) {
		res += size[i] * pr[j++] % MOD;
		res %= MOD;
	}
	for (int i = 0; i < max(n - m, 0ll); i++) {
		res = (res + size[i]) % MOD;
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
