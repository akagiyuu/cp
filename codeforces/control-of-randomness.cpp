#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;
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

void solve()
{
	int n, queries;
	cin >> n >> queries;
	vector<vector<int> > adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> p(n, 0);
	queue<int> q;
	vector<bool> visited(n, false);
	q.push(0);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (visited[u])
			continue;
		visited[u] = true;
		for (int v : adj[u]) {
			if (visited[v])
				continue;
			p[v] = u;
			q.push(v);
		}
	}
	while (queries--) {
		int u, coin;
		cin >> u >> coin;
		u--;
		int res = 0;
		vector<int> b;
		for (int i = 0; u > 0; i++, u = p[u]) {
			if (i % 2 == 0) {
				res = add(res, 1);
				continue;
			}
			b.push_back(2 * adj[u].size() - 1);
		}
		sort(b.begin(), b.end());
		int m = b.size();
		for (int i = m - 1; i >= 0; i--) {
			if (coin == 0) {
				res = add(res, b[i] % MOD);
				continue;
			}
			coin--;
			res = add(res, 1);
		}
		cout << res << '\n';
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
