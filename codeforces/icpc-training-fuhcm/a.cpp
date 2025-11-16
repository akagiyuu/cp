#include <bits/stdc++.h>

#define int long long

using namespace std;


void solve()
{
	char tmp;
	int n;
	cin >> n;
	int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		cin >> tmp;
		if (tmp == '+')
			x++;
		else
			y++;
	}
	int diff = x - y;
	int q, a, b;
	cin >> q;
	while (q--) {
		cin >> a >> b;
		int denom = a - b;
		if (denom == 0 && diff == 0) {
			cout << "YES\n";
			continue;
		}
		if (denom == 0 && diff != 0) {
			cout << "NO\n";
			continue;
		}
		if (b * diff % denom != 0 || a * diff % denom != 0) {
			cout << "NO\n";
			continue;
		}
		int t = a * diff / denom;
		int left = max(-t, 0ll);
		int right = min(y, x - t);
		if (left <= right)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
