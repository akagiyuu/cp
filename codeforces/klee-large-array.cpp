#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, k;
	cin >> n >> k;
	auto f = [k](int i) { return 2 * k * i + i * (i - 1); };
	int s = k * n + n * (n - 1) / 2;

	int l = 0, r = n - 1;
	while (l < r) {
		int mid = (l + r) / 2;
		if (f(mid) <= s) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	int res = abs(f(l) - s);
	if (l > 0)
		res = min(res, abs(f(l - 1) - s));
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
