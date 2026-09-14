#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>

const int MOD = 1000000007;
const int N = 2e5 + 7;
int fact[N], ifact[N];

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

void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % MOD;
	ifact[N - 1] = inverse(fact[N - 1]);
	for (int i = N - 2; i >= 0; i--)
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}
int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int n, k;
vector<vector<int> > adj;
vector<pi> edges;
vector<int> p, sz;
vector<bool> visited;
void dfs(int u)
{
	if (visited[u])
		return;
	visited[u] = true;
	sz[u] = 1;
	for (auto v : adj[u]) {
		if (visited[v])
			continue;
		p[v] = u;
		dfs(v);
		sz[u] += sz[v];
	}
}

int solve()
{
	cin >> n >> k;
	adj.assign(n, {});
	edges.clear();
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
		edges.push_back({ u, v });
	}
	if (k & 1)
		return 1;
	visited.assign(n, false);
	p.assign(n, 0);
	sz.assign(n, 0);
	dfs(0);
	int res = 0;
	for (auto [u, v] : edges) {
		if (u == p[v])
			swap(u, v);
		res = add(res, C(sz[u], k / 2) * C(n - sz[u], k / 2) % MOD);
	}
	res = res * inverse(C(n, k)) % MOD;
	res = add(res, 1);
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	cout << solve() << '\n';
}
