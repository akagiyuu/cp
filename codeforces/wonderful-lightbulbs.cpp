#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve()
{
	int n;
	cin >> n;
	map<int, int> cnt_x, cnt_diag;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		cnt_x[x] ^= 1;
		cnt_diag[x + y] ^= 1;
	}
	int X = 0;
	for (auto [x, c] : cnt_x) {
		if (c == 1) {
			X = x;
			break;
		}
	}

	int Y = 0;
	for (auto [diag, c] : cnt_diag) {
		if(c == 1) {
			Y = diag - X;
			break;
		}
	}

	cout << X << ' ' << Y << '\n';
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
