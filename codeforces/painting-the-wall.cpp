#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const int MOD = 1000000007;

void solve()
{
	int n, m;
	cin >> n >> m;

	set<int> rs, cs;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		rs.insert(x);
		cs.insert(y);
	}

	int rmax = n - rs.size();
	int cmax = n - cs.size();
	vector<vector<double> > dp(rmax + 1, vector<double>(cmax + 1, 0));
	for (int r = 0; r <= rmax; r++) {
		for (int c = 0; c <= cmax; c++) {
			if(r == 0 && c == 0) continue;
			if (r > 0) {
				dp[r][c] += r * (n - c) * (dp[r - 1][c]);
			}
			if (c > 0) {
				dp[r][c] += (n - r) * c * (dp[r][c - 1]);
			}
			if (r > 0 && c > 0) {
				dp[r][c] += r * c * (dp[r - 1][c - 1]);
			}
			double a = (n - r) * (n - c);
			double b = n * n;
			dp[r][c] += b;
			if(b != a) {
				dp[r][c] /= b - a;
			}
		}
	}
	cout << fixed << setprecision(10) << dp[rmax][cmax] << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
