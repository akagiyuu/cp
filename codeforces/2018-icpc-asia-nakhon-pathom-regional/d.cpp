#include <bits/stdc++.h>

using namespace std;

#define int long long
const int BUS_LENGTH = 10;

int solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (n == 0)
		return 0;

	int res = 0;
	int i = 0;
	int cur_bus = a[i] + BUS_LENGTH;
	while (i < n) {
		cur_bus = a[i] + BUS_LENGTH;
		res++;
		i = upper_bound(a.begin() + i, a.end(), cur_bus + BUS_LENGTH) - a.begin();
		// cout << i << "\n";
	}
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
