#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll n;
vector<vector<ll> > adj;
vector<bool> visited;
vector<ll> s;

void dfs(int v)
{
	visited[v] = true;
	for (int u : adj[v]) {
		if (!visited[u]) {
			dfs(u);
		}
	}
	s.push_back(v);
}

void solve()
{
	ll u, v, x, y;
	cin >> n;
	s.clear();
    adj.reserve(n);
	adj = vector<vector<ll> >(n);
	visited = vector<bool>(n, false);

	for (ll i = 0; i < n - 1; i++) {
		cin >> u >> v >> x >> y;
		u--;
		v--;
		if (x > y)
			adj[u].push_back(v);
		else
			adj[v].push_back(u);
	}
	for (int i = 0; i < n; ++i) {
		if (!visited[i]) {
			dfs(i);
		}
	}
	vector<ll> res(n);
	for (ll i = 0; i < n; i++) {
		res[s[i]] = i + 1;
	}
    for (ll i = 0; i < n; i++) {
        cout << res[i] << " ";
    }
    cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
