#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve()
{
	int n, p, w, d;
	cin >> n >> p >> w >> d;

	int num = w * n - p;
	int denom = w - d;
	if (denom < 0) {
		cout << -1 << "\n";
		return;
	}
	int left = 0;
	int right = w - 1;
	for (int y = left; y <= right; y++) {
		int wx = p - d * y;
		if (wx % w != 0)
			continue;
		int x = wx / w;
		int z = n - x - y;
		if (0 <= x && x <= n && 0 <= y && y <= n && 0 <= z && z <= n) {
			cout << x << " " << y << " " << z << "\n";
			return;
		}
	}
	cout << -1 << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
