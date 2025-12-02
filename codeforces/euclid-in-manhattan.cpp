#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

const double INF = 1e18;
const int THREDHOLD = 25;

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> widths(n), width_gaps(n), heights(m), height_gaps(m);
	for (int i = 0; i < n; i++) {
		cin >> widths[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> width_gaps[i];
	}
	width_gaps.pop_back();

	for (int i = 0; i < m; i++) {
		cin >> heights[i];
	}
	for (int i = 0; i < m; i++) {
		cin >> height_gaps[i];
	}
	height_gaps.pop_back();

	vector<int> width_prefix(2 * n);
	width_prefix[0] = 0;
	for (int i = 1; i < 2 * n; i++) {
		width_prefix[i] = width_prefix[i - 1];
		if (i % 2 == 0)
			width_prefix[i] += width_gaps[i / 2 - 1];
		else
			width_prefix[i] += widths[i / 2];
	}

	vector<int> height_prefix(2 * m);
	height_prefix[0] = 0;
	for (int i = 1; i < 2 * m; i++) {
		height_prefix[i] = height_prefix[i - 1];
		if (i % 2 == 0)
			height_prefix[i] += height_gaps[i / 2 - 1];
		else
			height_prefix[i] += heights[i / 2];
	}

	auto dist = [&](int i1, int j1, int i2, int j2) {
		double dw = width_prefix[i2] - width_prefix[i1];
		double dh = height_prefix[j2] - height_prefix[j1];
		if (dw == 0)
			return dh;
		if (dh == 0)
			return dw;
		return sqrtl(dw * dw + dh * dh);
	};

	vector<vector<double> > dp(2 * n, vector<double>(2 * m, INF));
	dp[0][0] = 0;
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 0; j < 2 * m; j++) {
			if (i == 0 && j == 0)
				continue;
			if (i > 0)
				dp[i][j] = min(dp[i][j], dp[i - 1][j] + dist(i - 1, j, i, j));
			if (j > 0)
				dp[i][j] = min(dp[i][j], dp[i][j - 1] + dist(i, j - 1, i, j));

			if (i % 2 == 0 && i > 0) {
				for (int k = max(j - THREDHOLD, 0ll); k < j; k++) {
					dp[i][j] = min(dp[i][j], dp[i - 1][k] + dist(i - 1, k, i, j));
				}
				continue;
			}
			if (j % 2 == 0 && j > 0) {
				for (int k = max(i - THREDHOLD, 0ll); k < i; k++) {
					dp[i][j] = min(dp[i][j], dp[k][j - 1] + dist(k, j - 1, i, j));
				}
				continue;
			}
		}
	}
	// for (int i = 0; i < 2 * n; i++) {
	// 	for (int j = 0; j < 2 * m; j++) {
	// 		cout << dp[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }
	cout << fixed << setprecision(10) << dp[2 * n - 1][2 * m - 1] << "\n";
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
