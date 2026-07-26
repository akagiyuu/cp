#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

int solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int s = 0, m = 0;
	for (int i = 0; i < n; i++) {
		s += a[i];
		m = max(m, a[i]);
	}

	for (int d = n; d >= 1; d--) {
		int cnt = max(m, (s + d - 1) / d);
		if (cnt * d <= s + k)
			return d;
	}

	return 1;
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
