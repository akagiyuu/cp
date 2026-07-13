#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>

const int MOD = 1000000007;
const int N = 17;

void solve()
{
	int n, q;
	cin >> n >> q;

	vector<vector<pi> > adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v, d;
		cin >> u >> v >> d;
		u--;
		v--;
		adj[u].push_back({ v, d });
		adj[v].push_back({ u, d });
	}

	vector<int> h(n, 0), dist(n, 0);
	queue<int> s;
	vector<bool> visited(n, false);
	vector<int> p(n, -1);

	s.push(0);
	while (!s.empty()) {
		int u = s.front();
		s.pop();
		if (visited[u])
			continue;
		visited[u] = true;
		for (auto [v, d] : adj[u]) {
			if (visited[v])
				continue;
			p[v] = u;
			h[v] = h[u] + 1;
			dist[v] = dist[u] + d;
			s.push(v);
		}
	}

	vector<vector<int> > up(n, vector<int>(N, 0));
	for (int u = 1; u < n; u++)
		up[u][0] = p[u];
	for (int j = 1; j < N; j++) {
		for (int u = 1; u < n; u++) {
			up[u][j] = up[up[u][j - 1]][j - 1];
		}
	}

	auto kth_ancestor = [up](int u, int k) {
		for (int j = 0; j < N; j++) {
			if ((k >> j) & 1)
				u = up[u][j];
		}
		return u;
	};

	while (q--) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		if (h[v] > h[u])
			swap(u, v);
		int res = dist[u] + dist[v];
		u = kth_ancestor(u, h[u] - h[v]);
		if (u != v) {
			for (int j = N - 1; j >= 0; j--) {
				if (up[u][j] != up[v][j]) {
					u = up[u][j];
					v = up[v][j];
				}
			}
			u = up[u][0];
		}
		res -= 2 * dist[u];
		cout << res << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
