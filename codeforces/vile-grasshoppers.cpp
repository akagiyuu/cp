#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int p, y;
	cin >> p >> y;
	while (y >= p) {
		int d = y;
		for (int i = 2; i * i <= y; i++) {
			if (y % i != 0)
				continue;
			d = i;
			break;
		}
		if (d > p) {
			cout << y << "\n";
			return;
		}
		y--;
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
