#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>

const int MOD = 1000000007;
const int INF = 1e13;

struct State {
	int u;
	bool is_riding;
	int d;
	State(int _u, bool _is_riding, int _d)
	{
		u = _u;
		is_riding = _is_riding;
		d = _d;
	}
	bool operator<(const State &other) const
	{
		return d > other.d;
	}
};

array<vector<int>, 2> cal_dist(int start, const vector<vector<pi> > &adj, const vector<bool> &is_horse)
{
	int n = adj.size();

	array<vector<int>, 2> dist = { vector<int>(n, INF), vector<int>(n, INF) };
	priority_queue<State, vector<State> > q;
	dist[0][start] = 0;
	q.push(State(start, false, 0));
	while (!q.empty()) {
		auto [u, is_riding, d] = q.top();
		q.pop();
		if (d != dist[is_riding][u])
			continue;
		for (auto [v, w] : adj[u]) {
			int cur_is_riding = is_riding || is_horse[u];
			if (cur_is_riding)
				w >>= 1;
			if (d + w < dist[cur_is_riding][v]) {
				dist[cur_is_riding][v] = d + w;
				q.push(State(v, cur_is_riding, d + w));
			}
		}
	}

	return dist;
}

void solve()
{
	int n, m, h;
	cin >> n >> m >> h;
	vector<bool> is_horse(n, false);
	for (int i = 0; i < h; i++) {
		int u;
		cin >> u;
		u--;
		is_horse[u] = true;
	}
	vector<vector<pi> > adj(n);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		adj[u].push_back({ v, w });
		adj[v].push_back({ u, w });
	}

	auto dist_a = cal_dist(0, adj, is_horse);
	auto dist_b = cal_dist(n - 1, adj, is_horse);

	int res = INF;
	for (int i = 0; i < n; i++) {
		int cur = INF;
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				cur = min(cur, max(dist_a[j][i], dist_b[k][i]));
			}
		}
		res = min(res, cur);
	}
	if (res == INF)
		cout << -1 << "\n";
	else
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
