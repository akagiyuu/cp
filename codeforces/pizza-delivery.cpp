#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 1000000007;

int dist(const pi &a, const pi &b)
{
	return abs(a.fi - b.fi) + abs(a.se - b.se);
}

void solve()
{
	int n;
	cin >> n;
	pi A, B;
	cin >> A.fi >> A.se;
	cin >> B.fi >> B.se;

	vector<pi> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i].fi;
	for (int i = 0; i < n; i++)
		cin >> a[i].se;
	sort(a.begin(), a.end());

	vector<vector<pi> > layers = { { A } };
	vector<pi> cur = { a[0] };
	for (int i = 1; i < n; i++) {
		if (a[i].fi == cur[0].fi) {
			cur.push_back(a[i]);
			continue;
		}

		layers.push_back(cur);
		cur = { a[i] };
	}
	layers.push_back(cur);
	layers.push_back({ B });

	int sz = layers.size();
	vector<array<int, 2> > dp(sz);
	dp[0] = { 0, 0 };
	for (int i = 1; i < sz; i++) {
		dp[i] = { LLONG_MAX, LLONG_MAX };
		int l = dist(layers[i][0], layers[i].back());

		for (int cur_idx = 0; cur_idx < 2; cur_idx++) {
			for (int pre_idx = 0; pre_idx < 2; pre_idx++) {
				int d_between = dist(cur_idx == 0 ? layers[i].back() : layers[i][0],
						     pre_idx == 0 ? layers[i - 1][0] : layers[i - 1].back());

				dp[i][cur_idx] = min(dp[i][cur_idx], dp[i - 1][pre_idx] + d_between + l);
			}
		}
	}
	// cout << "TEST:\n";
	// for (int i = 0; i < layers.size(); i++) {
	// 	cout << "Layer " << i << "\n";
	// 	for (auto x : layers[i]) {
	// 		cout << x.fi << " " << x.se << "\n";
	// 	}
	// 	cout << "\n";
	// 	cout << "DP: " << dp[i][0] << " " << dp[i][1] << "\n";
	// }
	cout << dp[sz - 1][0] << "\n";
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
