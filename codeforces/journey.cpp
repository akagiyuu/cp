#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

double expected_length(ll i, vector<vector<ll> > &adj, vector<bool> &visited, vector<double> &dp)
{
	if (dp[i] != -1)
		return dp[i];
	ll count = 0;
	double sum = 0;
	for (auto x : adj[i]) {
		if (visited[x])
			continue;

		count++;
		visited[x] = true;
		sum += expected_length(x, adj, visited, dp);
		visited[x] = false;
	}

	if (count == 0) {
		dp[i] = 0;
	} else {
		dp[i] = sum / (double)count + 1;
	}
	return dp[i];
}

void solve()
{
	ll n, x, y;
	cin >> n;
	vector<vector<ll> > adj(n);
	for (ll i = 0; i < n - 1; i++) {
		cin >> x >> y;
		x--;
		y--;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	vector<bool> visited(n);
	visited[0] = true;
	vector<double> dp(n, -1);

	double res = expected_length(0, adj, visited, dp);
	cout << setprecision(10) << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
