#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define pi array<int, 2>

const int MOD = 1000000007;
const int N = 6;
const int INF = 1e9 + 7;

int encode(char c)
{
	switch (c) {
	case 'B':
		return 0;
	case 'G':
		return 1;
	case 'R':
		return 2;
	case 'Y':
		return 3;
	default:
		assert(false);
	}
}

int encode(pi x)
{
	if (x == array{ 0ll, 1ll })
		return 0;
	if (x == array{ 0ll, 2ll })
		return 1;
	if (x == array{ 0ll, 3ll })
		return 2;
	if (x == array{ 1ll, 2ll })
		return 3;
	if (x == array{ 1ll, 3ll })
		return 4;
	if (x == array{ 2ll, 3ll })
		return 5;
	assert(false);
}

bool can_move(pi x, pi y)
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (x[i] == y[j])
				return true;
		}
	}
	return false;
}

void solve()
{
	int n, q;
	cin >> n >> q;
	vector<pi> cities(n);
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		cities[i] = { encode(s[0]), encode(s[1]) };
		if (cities[i][0] > cities[i][1])
			swap(cities[i][0], cities[i][1]);
	}

	vector<array<int, N> > idxs_left(n);
	for (int j = 0; j < N; j++) {
		idxs_left[0][j] = -1;
	}
	for (int i = 1; i < n; i++) {
		idxs_left[i] = idxs_left[i - 1];
		idxs_left[i][encode(cities[i - 1])] = i - 1;
	}

	vector<array<int, N> > idxs_right(n);
	for (int j = 0; j < N; j++) {
		idxs_right[n - 1][j] = -1;
	}
	for (int i = n - 2; i >= 0; i--) {
		idxs_right[i] = idxs_right[i + 1];
		idxs_right[i][encode(cities[i + 1])] = i + 1;
	}

	while (q--) {
		int i, j;
		cin >> i >> j;
		i--;
		j--;
		if (i > j)
			swap(i, j);
		if (i == j) {
			cout << 0 << "\n";
			continue;
		}
		if (can_move(cities[i], cities[j])) {
			cout << j - i << "\n";
			continue;
		}

		int res = INF;
		for (auto p1 : cities[i]) {
			for (auto p2 : cities[j]) {
				pi mid = { p1, p2 };
				if (mid[0] > mid[1])
					swap(mid[0], mid[1]);
				int m = encode(mid);
				if (idxs_left[j][m] != -1) {
					int cur = abs(i - idxs_left[j][m]) + abs(j - idxs_left[j][m]);
					// cout << mid[0] << ", " << mid[1] << " -> " << cur << "\n";
					res = min(res, cur);
				}
				if (idxs_right[j][m] != -1) {
					int cur = abs(i - idxs_right[j][m]) + abs(j - idxs_right[j][m]);
					// cout << mid[0] << ", " << mid[1] << " -> " << cur << "\n";
					res = min(res, cur);
				}
			}
		}
		// cout << "\n";
		//
		if (res == INF)
			cout << -1 << "\n";
		else
			cout << res << "\n";
	}
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
