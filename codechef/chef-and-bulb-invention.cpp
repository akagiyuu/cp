#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, p, k;
	cin >> n >> p >> k;
	int r0 = p % k;
	int res = r0;
	res += (p - r0) / k + 1;
	n--;
	r0--;
	for (int q = (n - r0) / k; q <= n / k; q++) {
		int left = max(n - k * q - k + 1, 0ll);
		int right = min(n - k * q, r0);
		int cnt = max(right - left + 1, 0ll);
		res += q * cnt;
	}
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
