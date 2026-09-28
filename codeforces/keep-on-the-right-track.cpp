#include <bits/stdc++.h>

#define int long long

using namespace std;

typedef pair<int, int> ii;

const int N = 1e6 + 7;
const long long INF = 1e18 + 7;
const long long MOD = 998244353;

vector<pair<ii, int> > adj[N];
vector<pair<ii, int> > rev[N];

char a[N];

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
void solve()
{
	int n, m, t;
	cin >> n >> m >> t;

	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		if (u == t)
			continue;
		adj[u].push_back({ { v, w }, i });
		rev[v].push_back({ { u, w }, i });
	}

	priority_queue<ii, vector<ii>, greater<ii> > pq;

	vector<int> dist(n + 1, INF);
	vector<int> cnt(n + 1, 0);

	vector<int> waysEdge(m + 1, 0);

	dist[t] = 0;
	cnt[t] = 1;
	pq.push({ 0, t });

	while (!pq.empty()) {
		int u = pq.top().second;
		int du = pq.top().first;
		pq.pop();

		if (du != dist[u])
			continue;

		for (auto [p, id] : rev[u]) {
			int v = p.first;
			int w = p.second;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				cnt[v] = cnt[u];
				pq.push({ dist[v], v });
			} else if (dist[v] == dist[u] + w) {
				cnt[v] = add(cnt[v], cnt[u]);
			}
		}
	}

	// Topo sort in reverse graph
	vector<int> topo;
	vector<int> inDegree(n + 1, 0);

	vector<int> dp(n + 1, 0);

	for (int i = 1; i <= n; ++i) {
		for (auto [p, id] : rev[i]) {
			int v = p.first;
			int w = p.second;
			inDegree[v]++;
		}
	}

	queue<int> q;
	for (int i = 1; i <= n; ++i) {
		if (inDegree[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		topo.push_back(u);

		for (auto [p, id] : rev[u]) {
			int v = p.first;
			int w = p.second;
			inDegree[v]--;
			if (a[v] == '0') {
				dp[v] = add(dp[v], add(dp[u], w));
			} else if (dist[v] == dist[u] + w) {
				dp[v] = add(dp[v], cnt[u] * add(dp[u], w) % MOD);
			}
			if (inDegree[v] == 0) {
				if (a[v] == '0') {
					int sz = adj[v].size();
					if (sz > 0)
						dp[v] = (dp[v] * inverse(sz)) % MOD;
				} else {
					if (cnt[v] > 0)
						dp[v] = (dp[v] * inverse(cnt[v])) % MOD;
				}
				q.push(v);
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		cout << dp[i] << ' ';
	}
}

signed main()
{
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	if (fopen("input.txt", "r")) {
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	}
	int t = 1;
	//cin >> t;
	while (t--)
		solve();
	return 0;
}
