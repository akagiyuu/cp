#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	int res = 0;
	for (int i = 0; i < n; i += k) {
		int cnt = 0;
		for (int j = 0; j < k; j++)
			cnt += (s[i + j] == '1');
		if (cnt == k)
			res++;
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
