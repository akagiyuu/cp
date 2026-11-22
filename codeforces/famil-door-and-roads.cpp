#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double
#define ii pair<int, int>

const int N = 1e5 + 7;
const int M = 18;

int n, m;
vector<vector<int> > adj;
vector<vector<int> > children;
int sz[N], sum_down[N], sum[N], d[N];
int up[N][M];

void dfs(int u)
{
	if (sz[u] > 0)
		return;

	sz[u] = 1;
	for (auto v : adj[u]) {
		if (v == up[u][0])
			continue;

		d[v] = d[u] + 1;
		up[v][0] = u;
		children[u].push_back(v);
		for (int j = 1; j < M; j++)
			up[v][j] = up[up[v][j - 1]][j - 1];

		dfs(v);

		sz[u] += sz[v];
		sum_down[u] += sum_down[v] + sz[v];
	}
}
void dfs_sum(int u)
{
	for (auto v : children[u]) {
		sum[v] = sum[u] + n - 2 * sz[v];
		dfs_sum(v);
	}
}
ii get(int u, int v)
{
	if (v == up[u][0])
		return { sz[u], sum_down[u] };
	return { n - sz[v], sum[u] - sum_down[v] - sz[v] };
}
int jump(int u, int k)
{
	for (int j = 0; j < M; j++)
		if (k >> j & 1)
			u = up[u][j];
	return u;
}
int lca(int u, int v)
{
	if (d[u] != d[v]) {
		if (d[u] < d[v])
			swap(u, v);

		int k = d[u] - d[v];
		for (int j = 0; (1 << j) <= k; j++)
			if (k >> j & 1)
				u = up[u][j];
	}
	if (u == v)
		return u;
	int k = __lg(d[u]);
	for (int j = k; j >= 0; j--)
		if (up[u][j] != up[v][j])
			u = up[u][j], v = up[v][j];
	return up[u][0];
}

void solve()
{
	cin >> n >> m;
	adj.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	children.resize(n);
	dfs(0);
	sum[0] = sum_down[0];
	dfs_sum(0);
	while (m--) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		int c = lca(u, v);
		if (c != u && c != v) {
			double res =
				d[u] + d[v] - 2 * d[c] + 1 + (double)sum_down[u] / sz[u] + (double)sum_down[v] / sz[v];
			cout << fixed << setprecision(6) << res << '\n';
		} else {
			if (c == v)
				swap(u, v);
			int x = jump(v, d[v] - d[u] - 1);
			double res = d[v] - d[u] + 1 + (double)sum_down[v] / sz[v] +
				     (double)(sum[u] - sum_down[x] - sz[x]) / (n - sz[x]);
			cout << fixed << setprecision(6) << res << '\n';
		}
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
