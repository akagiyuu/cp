#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n), rev_a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
		rev_a[a[i]] = i;
	}

	int res = 1;
	int cnt = 1;
	for (int cur = 1; cur < n; cur++) {
		int i = rev_a[cur - 1];
		int j = rev_a[cur];
		if (i < j) {
			cnt++;
		} else {
			res = max(res, cnt);
			cnt = 1;
		}
	}
	res = max(res, cnt);

	cout << n - res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
