#include <bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e18;

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> a(n), dist(n, INF);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] > 0)
			dist[i] = 0;
	}
	for (int i = 1; i < n; i++) {
		dist[i] = min(dist[i], dist[i - 1] + 1);
	}
	for (int i = n - 2; i >= 0; i--) {
		dist[i] = min(dist[i], dist[i + 1] + 1);
	}
	int res = 0;
	for (int i = 0; i < n; i++) {
		res = max(res, (dist[i] + k - 1) / k);
	}
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
