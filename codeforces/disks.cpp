#include <bits/stdc++.h>

using namespace std;

#define int long long

struct Data {
	int x, y, r;
};

int sq_dist(int x1, int y1, int x2, int y2)
{
	int dx = x1 - x2;
	int dy = y1 - y2;
	return dx * dx + dy * dy;
}

void solve()
{
	int n;
	cin >> n;

	vector<Data> disks(n);
	for (int i = 0; i < n; i++) {
		cin >> disks[i].x >> disks[i].y >> disks[i].r;
	}

	vector<vector<int> > adj(n);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int d = sq_dist(disks[i].x, disks[i].y, disks[j].x, disks[j].y);
			int r_sum = disks[i].r + disks[j].r;
			if (d == r_sum * r_sum) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}

	vector<bool> visited(n, false);
	vector<int> color(n, 0);

	for (int i = 0; i < n; i++) {
		if (visited[i])
			continue;

		queue<int> q;
		q.push(i);
		visited[i] = true;
		color[i] = 1;

		bool is_bipartite = true;
		int component_sum = 0;

		while (!q.empty()) {
			int u = q.front();
			q.pop();

			component_sum += color[u];

			for (int v : adj[u]) {
				if (!visited[v]) {
					visited[v] = true;
					color[v] = -color[u];
					q.push(v);
				} else if (color[v] != -color[u]) {
					is_bipartite = false;
				}
			}
		}

		if (is_bipartite && component_sum != 0) {
			cout << "YES\n";
			return;
		}
	}

	cout << "NO\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	solve();

	return 0;
}
