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
	sort(a.begin(), a.end());
	deque<int> res;
	int i = n - 1;
	while (i >= 0) {
		res.push_back(a[i]);
		i--;
		if (i > 0) {
			res.push_front(a[i]);
			i--;
		}
	}
	int x = 0;
	for (int i = 0; i < n; i++) {
		x += res[i] * res[(i + 1) % n];
	}
	cout << x << "\n";
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
