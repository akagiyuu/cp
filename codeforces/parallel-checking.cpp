#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, T;
	cin >> n >> T;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	auto f = [&a](int d) {
		int res = 0;
		for (auto x : a) {
			res += (x + d - 1) / d;
		}
		return res;
	};

	int r = 0;
	for (auto x : a)
		r = max(r, x);
	r++;
	int l = 1;
	while (l < r) {
		int m = (l + r) / 2;
		if (f(m) <= T) {
			r = m;
		} else {
			l = m + 1;
		}
	}
	cout << l << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
