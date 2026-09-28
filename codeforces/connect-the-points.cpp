#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int N = 3;
const int INF = 1e18;

int dist(const pi &a, const pi &b)
{
	return abs(a.fi - b.fi) + abs(a.se - b.se);
}

void solve()
{
	vector<pi> a(N);
	for (int i = 0; i < N; i++) {
		cin >> a[i].fi >> a[i].se;
	}
	int min = INF;
	vector<int> min_a(N);
	for (int j = 0; j < N; j++) {
		int i = (j + N - 1) % N;
		int k = (j + 1) % N;
		int cur = dist(a[j], a[i]) + dist(a[j], a[k]);
		if (cur < min) {
			min_a = { i, j, k };
			min = cur;
		}
	}
	for (int i = 0; i < N - 1; i++) {
		int j = i + 1;
		auto [x1, y1] = a[min_a[i]];
		auto [x2, y2] = a[min_a[j]];
		cout << x1 << ' ' << y1 << ' ' << x1 << ' ' << y2 << '\n';
		cout << x1 << ' ' << y2 << ' ' << x2 << ' ' << y2 << '\n';
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
