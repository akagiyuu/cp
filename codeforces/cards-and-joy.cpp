#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

int knapsack(int t, int w, int k, const vector<int> &h)
{
	vector<int> dp(w + 1, 0);
	for (int i = 0; i < t; i++) {
		vector<int> ndp = dp;
		for (int j = 0; j <= w; j++) {
			for (int x = 1; x <= k; x++) {
				if (j - x < 0)
					break;
				ndp[j] = max(ndp[j], dp[j - x] + h[x]);
			}
			if (j > 0)
				ndp[j] = max(ndp[j], ndp[j - 1]);
		}
		dp = ndp;
	}
	return dp[w];
}

void solve()
{
	int n, k;
	cin >> n >> k;
	int m = n * k;
	map<int, int> cnt_card;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		cnt_card[x]++;
	}
	map<int, int> cnt_people;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		cnt_people[x]++;
	}
	vector<int> h(k + 1, 0);
	for (int i = 1; i <= k; i++)
		cin >> h[i];
	int res = 0;
	for (auto [f, t] : cnt_people) {
		int w = cnt_card[f];
		// cout << f << ' ' << t << ' ' << w << ' ' << knapsack(t, w, k, h) << '\n';
		res += knapsack(t, w, k, h);
	}
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
