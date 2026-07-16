#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 1000000007;

vector<int> solve()
{
	int n, k;
	cin >> n >> k;
	k ^= n;
	vector<int> res;
	if (k == 0) {
		for (int i = 1; i < n; i++)
			res.push_back(i);
		res.push_back(0);
		return res;
	}

	int y = 1ll << __lg(k);
	int x = k - y;
	// cout << "TEST: " << k << " " < < < < "\n";
	if (x > n - 1 || y > n - 1) {
		return res;
	}

	for (int i = 0; i < n; i++) {
		if (i == 0 || i == x || i == y)
			continue;
		res.push_back(i);
	}
	if (x > 0) {
		res.push_back(0);
		res.push_back(x);
		res.push_back(y);
	} else {
		res.push_back(x);
		res.push_back(y);
	}
	if ((int)res.size() != n)
		return vector<int>();
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		auto res = solve();
		if (res.empty())
			cout << "NO\n";
		else {
			cout << "YES\n";
			for (auto x : res)
				cout << x << " ";
			cout << "\n";
		}
	}
}
