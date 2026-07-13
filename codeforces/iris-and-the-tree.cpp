#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 20;

vector<int> h, p, mx, mi;
vector<vector<int> > c, up;

void build_height()
{
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (auto v : c[u]) {
			h[v] = h[u] + 1;
			q.push(v);
		}
	}
}

void build_boundaries(int u)
{
	mx[u] = u;
	mi[u] = u;
	for (auto v : c[u]) {
		build_boundaries(v);
		mx[u] = max(mx[u], mx[v]);
		mi[u] = min(mi[u], mi[v]);
	}
}

void build_ancestor_jump()
{
	int n = p.size();
	for (int u = 1; u < n; u++)
		up[u][0] = p[u];
	for (int j = 1; j < N; j++) {
		for (int u = 1; u < n; u++) {
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
	int n, w;
	cin >> n >> w;

	p.assign(n, 0);
	c.assign(n, vector<int>());
	h.assign(n, 0);
	mx.assign(n, 0);
	mi.assign(n, 0);
	up.assign(n, vector<int>(N, 0));
	for (int i = 1; i < n; i++) {
		cin >> p[i];
		p[i]--;
		c[p[i]].push_back(i);
	}

	build_boundaries(0);
	build_height();
	build_ancestor_jump();

	vector<int> cnt(n);
	for (int i = 0; i < n; i++) {
		int u = i;
		int v = (i + 1) % n;
		cnt[i] = h[u] + h[v];
		u = lca(u, v);
		cnt[i] -= 2 * h[u];
	}

	int fixed = 0;
	int flexible_cnt = n;

	for (int i = 0; i < n - 1; i++) {
		int v, d;
		cin >> v >> d;
		v--;
		int u = p[v];
		// cout << "START: " << i << " " << u << " " << v << "\n";

		set<int> s;
		if ((u + 1) % n == v) {
			s.insert(u);
		}
		if ((u + n - 1) % n == v) {
			s.insert(v);
		}
		if (h[lca(mx[v], (mx[v] + 1) % n)] <= h[u]) {
			s.insert(mx[v]);
		}
		if (h[lca(mi[v], (mi[v] + n - 1) % n)] <= h[u]) {
			s.insert((mi[v] + n - 1) % n);
		}

		for (auto x : s) {
			cnt[x]--;
			fixed += d;
			// cout << x << " " << (x + 1) % n << "\n";
			if (cnt[x] == 0) {
				// cout << x << " ";
				flexible_cnt--;
			}
		}
		// cout << "\n";

		w -= d;
		// cout << fixed << " " << w << " " << flexible_cnt << " -> " << fixed + w * flexible_cnt << "\n";
		cout << fixed + w * flexible_cnt << " ";
	}
	cout << "\n";
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
