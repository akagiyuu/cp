#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int x = 0, y = 0, z = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] % 2 == 1)
			x++;
		if (a[i] % 4 == 0)
			y++;
		if (a[i] % 4 == 2)
			z++;
	}
	int res = max(x, max(y, z));
	cout << res << "\n";
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
