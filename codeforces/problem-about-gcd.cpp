#include <bits/stdc++.h>

using namespace std;

#define int long long

pair<int, int> solve()
{
	int l, r, g;
	cin >> l >> r >> g;
	l = (l + g - 1) / g;
	r = r / g;
	for (int dis = r - l; dis >= 0; dis--) {
		for (int i = l; i <= r - dis; i++) {
			int j = i + dis;
			if (gcd(i, j) == 1)
				return { i * g, j * g };
		}
	}
	return { -1, -1 };
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		auto [a, b] = solve();
		cout << a << " " << b << "\n";
	}
}
