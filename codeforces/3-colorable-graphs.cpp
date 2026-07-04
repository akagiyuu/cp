#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

int solve()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int> > adj(2 * n);
	vector<vector<bool> > is_adj(n, vector<bool>(n, false));
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
		is_adj[u][v - n] = true;
	}

	int res = 4;
	for (int i = 0; i < n; i++) {
		for (auto j : adj[i]) {
			if (j == i)
				continue;
			for (auto k : adj[j]) {
				if (k == j)
					continue;
				for (auto l : adj[k]) {
					if (l == k)
						continue;
					if (is_adj[i][l - n]) {
						cout << i << " " << j << " " << k << " " << l << "\n";
						return 2;
					} else
						res = min(res, 3ll);
				}
			}
		}
	}
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
