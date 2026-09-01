#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 1000000007;

int solve()
{
	int n, k;
	cin >> n >> k;
	int i = 0;
	int t = k - 1;
	while (i < n) {
		int q = i / t;
		int x = ((q + 1) * t - i + q) / (q + 1);
		if (i + x * (q + 1) >= n) {
			x = (n - i - 1) / (q + 1);
			return i + x * (q + 1) + 1;
		}
		i = i + x * (q + 1);
	}
	assert(false);
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
