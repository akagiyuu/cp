#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int cnt0 = 0;
	for (auto x : a)
		cnt0 += (x == 0);

	if (cnt0 == 1) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	string res(n, 'C');

	if (cnt0 >= 2) {
		bool first = true;
		for (int i = 0; i < n; i++) {
			if (a[i] == 0) {
				if (first) {
					res[i] = 'A';
					first = false;
				} else
					res[i] = 'B';
			}
		}
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
