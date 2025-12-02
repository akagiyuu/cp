#include <bits/stdc++.h>

#define int long long

using namespace std;

struct pt {
	int x, y;
};

void solve()
{
	int n;
	cin >> n;
	__int128 res = (__int128)n * (__int128)(n - 1) * (__int128)(n - 2);
	res /= (__int128)6;

	vector<int> cnt_x(n + 1, 0), cnt_y(n + 1, 0);
	vector<pt> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
		cnt_x[a[i].x]++;
		cnt_y[a[i].y]++;
	}
	for (int i = 0; i < n; i++) {
		res -= (cnt_x[a[i].x] - 1) * (cnt_y[a[i].y] - 1);
	}
	cout << (int)res << "\n";
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
