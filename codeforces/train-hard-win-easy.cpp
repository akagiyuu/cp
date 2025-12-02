#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<array<int, 3> > a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1];
		a[i][2] = i;
	}
	vector<int> res(n, 0);
	while (m--) {
		int i, j;
		cin >> i >> j;
		i--;
		j--;
		int cur = min(a[i][0] + a[j][1], a[i][1] + a[j][0]);
		res[i] -= cur;
		res[j] -= cur;
		// cout << i << " " << j << " " << cur << "\n";
	}
	// for (int i = 0; i < n; i++) {
	// 	cout << res[i] << " ";
	// }
	// cout << "\n";
	sort(a.begin(), a.end(), [](array<int, 3> &a, array<int, 3> &b) { return a[0] - a[1] < b[0] - b[1]; });
	// for (int i = 0; i < n; i++) {
	// 	cout << a[i][0] << " " << a[i][1] << " " << a[i][2] << "\n";
	// }
	// cout << "\n";
	vector<array<int, 2> > prefix(n);
	prefix[0][0] = a[0][0];
	prefix[0][1] = a[0][1];
	for (int i = 1; i < n; i++) {
		prefix[i] = prefix[i - 1];
		prefix[i][0] += a[i][0];
		prefix[i][1] += a[i][1];
	}
	auto cal = [&](int l, int r, int i) {
		if (l > r)
			return 0ll;
		array<int, 2> res;
		res = prefix[r];
		if (l > 0) {
			res[i] -= prefix[l - 1][i];
		}
		return res[i];
	};
	for (int i = 0; i < n; i++) {
		int cur = 0;
		cur += a[i][1] * i + cal(0, i - 1, 0);
		cur += a[i][0] * (n - 1 - i) + cal(i + 1, n - 1, 1);
		res[a[i][2]] += cur;
		// cout << a[i][2] << " " << cur << "\n";
	}
	for (int i = 0; i < n; i++) {
		cout << res[i] << " ";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
