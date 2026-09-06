#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	vector<int> c(n + 1);
	vector<int> pc(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		c[i] = a[i] - i * k;
		pc[i] = pc[i - 1] + c[i];
	}

	vector<int> res(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		if (i == 1 || i == n) {
			res[i] = 0;
			continue;
		}
		if (a[i + 1] - a[i - 1] <= k) {
			res[i] = 0;
			continue;
		}
		int cur = a[i - 1] - i * k;

		int l = i + 1;
		int r = n;
		int q = i;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (c[mid] > cur) {
				q = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}

		res[i] = pc[q] - pc[i] - (q - i) * cur;
	}
	for (int i = 1; i <= n; i++)
		cout << res[i] << " ";
	cout << "\n";
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
