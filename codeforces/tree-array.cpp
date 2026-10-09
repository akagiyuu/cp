#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 20;

int add(int x, int y)
{
	x += y;
	if (x >= MOD)
		x -= MOD;
	return x;
}
int sub(int x, int y)
{
	x -= y;
	if (x < 0)
		x += MOD;
	return x;
}
int powmod(int x, int e)
{
	int r = 1;
	while (e) {
		if (e & 1)
			r = r * x % MOD;
		x = x * x % MOD;
		e >>= 1;
	}
	return r;
}
int inverse(int x)
{
	return powmod(x, MOD - 2);
}

int n;
vector<int> h, p;
vector<vector<int> > up, adj;

void build(int r)
{
	h.assign(n, 0);
	p.assign(n, 0);
	up.assign(n, vector<int>(N, 0));
	vector<bool> visited(n, false);
	queue<int> q;
	q.push(r);
	p[r] = r;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (visited[u])
			continue;
		visited[u] = true;

		for (auto v : adj[u]) {
			if (visited[v])
				continue;
			h[v] = h[u] + 1;
			p[v] = u;
			q.push(v);
		}
	}
	int n = p.size();
	for (int u = 0; u < n; u++)
		up[u][0] = p[u];
	for (int j = 1; j < N; j++) {
		for (int u = 0; u < n; u++) {
			up[u][j] = up[up[u][j - 1]][j - 1];
		}
	}
}
int kth_ancestor(int u, int k)
{
	for (int j = 0; j < N; j++) {
		if ((k >> j) & 1) {
			u = up[u][j];
		}
	}
	return u;
};
int lca(int u, int v)
{
	if (h[v] > h[u])
		swap(u, v);
	u = kth_ancestor(u, h[u] - h[v]);
	if (u == v)
		return u;

	for (int j = N - 1; j >= 0; j--) {
		if (up[u][j] != up[v][j]) {
			u = up[u][j];
			v = up[v][j];
		}
	}
	u = up[u][0];
	return u;
}

void solve()
{
	cin >> n;
	adj.assign(n, vector<int>());
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<vector<int> > dp(n, vector<int>(n, 0));
	for (int x = 1; x < n; x++)
		dp[x][0] = 0;
	for (int y = 1; y < n; y++)
		dp[0][y] = 1;
	for (int x = 1; x < n; x++) {
		for (int y = 1; y < n; y++) {
			dp[x][y] = add(dp[x - 1][y], dp[x][y - 1]) * inverse(2) % MOD;
		}
	}

	int res = 0;
	for (int r = 0; r < n; r++) {
		build(r);
		for (int x = 1; x < n; x++) {
			for (int y = 0; y < x; y++) {
				int z = lca(x, y);
				int sz_x = h[x] - h[z];
				int sz_y = h[y] - h[z];
				res = add(res, dp[sz_x][sz_y]);
			}
		}
	}
	res = res * inverse(n) % MOD;
	cout << res << '\n';
}
signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
