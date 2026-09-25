#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>

const int INF = -1e18;

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<string> grid(n);
	for (int i = 0; i < n; i++)
		cin >> grid[i];
	int a = INF, b = INF, c = INF, d = INF;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 'W')
				continue;
			a = max(a, -i - j);
			b = max(b, -i + j);
			c = max(c, i - j);
			d = max(d, i + j);
		}
	}

	auto calc = [a, b, c, d](int x, int y) { return max(max(x + y + a, x - y + b), max(-x + y + c, -x - y + d)); };

	int min_i = 0, min_j = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (calc(i, j) < calc(min_i, min_j)) {
				min_i = i;
				min_j = j;
			}
		}
	}
	cout << min_i + 1 << ' ' << min_j + 1 << '\n';
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
