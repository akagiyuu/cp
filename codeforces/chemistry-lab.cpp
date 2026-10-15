#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

struct Data {
	int x, w, c;
};

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<Data> s(n);
	for (int i = 0; i < n; i++)
		cin >> s[i].x >> s[i].w >> s[i].c;
	sort(s.begin(), s.end(), [](const Data &a, const Data &b) { return a.x < b.x; });
	vector<double> dp(n);
	for (int i = 0; i < n; i++) {
		dp[i] = -s[i].w;
	}
	double res = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			double dx = (s[i].x - s[j].x) / 100.L;
			double cur = dp[j] + 0.5L * (s[i].c + s[j].c) * abs(dx) * k - s[i].w;
			dp[i] = max(dp[i], cur);
		}
		res = max(res, dp[i]);
	}
	cout << fixed << setprecision(6) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
