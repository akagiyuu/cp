#include <bits/stdc++.h>

using namespace std;

#define int long long

int n, k;
vector<vector<int> > adj;
vector<bool> removed;
vector<int> sz;

int calc_sz(int u, int p)
{
	sz[u] = 1;
	for (auto v : adj[u]) {
		if (v != p && !removed[v])
			sz[u] += calc_sz(v, u);
	}
	return sz[u];
}
int find_centroid(int u, int p, int total)
{
	for (auto v : adj[u]) {
		if (v != p && !removed[v] && sz[v] > total / 2)
			return find_centroid(v, u, total);
	}
	return u;
}
void build_dist(int u, int p, int d, vector<int> &dist)
{
	if (d > k)
		return;
	dist.push_back(d);
	for (auto v : adj[u]) {
		if (v == p || removed[v])
			continue;
		build_dist(v, u, d + 1, dist);
	}
}
int process_centroid(int c)
{
	vector<int> dist;
	vector<int> cnt(k + 1, 0);
	int res = 0;
	cnt[0] = 1;
	for (auto v : adj[c]) {
		if (removed[v])
			continue;
		dist.clear();
		build_dist(v, c, 1, dist);
		for (auto d : dist)
			res += cnt[k - d];
		for (auto d : dist)
			cnt[d]++;
	}
	return res;
}
int decompose(int u)
{
	int total = calc_sz(u, -1);
	int c = find_centroid(u, -1, total);
	removed[c] = true;
	int res = process_centroid(c);
	for (int v : adj[c]) {
		if (!removed[v])
			res += decompose(v);
	}
	return res;
}

int solve()
{
	cin >> n >> k;
	adj.assign(n, {});
	removed.assign(n, false);
	sz.assign(n, 0);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	return decompose(0);
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << '\n';
}
