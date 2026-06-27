#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, k;
	cin >> n >> k;
	int res = 0;
	for (int i = 0; i < 64; i++) {
		int cur = k * (1ll << i);
		if (n >= cur) {
			n -= cur;
			res += k;
			continue;
		}

		res += n / (1ll << i);

		break;
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
