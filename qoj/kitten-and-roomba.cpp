#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

double solve()
{
	int n, c;
	cin >> n >> c;
	c--;
	vector<vector<int> > adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int m;
	cin >> m;
	vector<int> a(m);
	for (int i = 0; i < m; i++) {
		cin >> a[i];
		a[i]--;
	}

	vector<bool> visited(n, false);
	queue<int> q;
	vector<int> parent(n, -1);
	q.push(0);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (visited[u])
			continue;
		visited[u] = true;
		for (auto v : adj[u]) {
			if (visited[v])
				continue;
			parent[v] = u;
			q.push(v);
		}
	}

	vector<double> f(m, 0), v(n, 0), s(n, 0);
	auto update = [&](int u, double x) {
		double prev = v[u];
		int p = parent[u];
		v[u] = x;
		if (p != -1) {
			s[p] -= prev;
			s[p] += x;
		}
	};
	auto get = [&](int u) {
		int p = parent[u];
		return s[u] + (p != -1 ? v[p] : 0);
	};
	f[m - 1] = 1;
	update(a[m - 1], 1);
	for (int i = m - 2; i >= 0; i--) {
		int u = a[i];
		f[i] = 1. + get(u) / (double)adj[u].size();
		update(u, f[i]);
	}

	for (int i = 0; i < m; i++)
		if (a[i] == c)
			return f[i];
	return 0;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << fixed << setprecision(10) << solve() << '\n';
}
