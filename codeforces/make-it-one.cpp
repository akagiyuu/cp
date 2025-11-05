#include <bits/stdc++.h>

#define int long long

using namespace std;


int solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (a[0] == 1)
		return 1;

	int res = n + 1;
	set<pair<int, int> > gcds, ngcds;
	gcds.insert({ a[0], 1 });
	for (int i = 1; i < n; i++) {
		ngcds.clear();
		for (auto [x, len] : gcds) {
			if (len > res)
				continue;

			ngcds.insert({ x, len });

			int tmp = gcd(x, a[i]);
			if (tmp == 1)
				res = min(res, len + 1);
			else
				ngcds.insert({ tmp, len + 1 });
		}
		gcds = ngcds;
	}
	if (res == n + 1)
		return -1;

	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
