#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> res(n);
	int cur = n;
	for (int i = 0; i < n / 2; i++) {
		res[i] = cur;
		cur--;
		res[n - 1 - i] = cur;
		cur--;
	}
	if (n % 2 == 1)
		res[n / 2] = cur;
	for (int i = 0; i < n; i++) {
		cout << res[i] << " ";
	}
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
