#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

bool solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		cnt += a[i] == 1;
	}
	if (cnt == n)
		return true;

	vector<int> point_cnts;
	if (n % 4 == 0)
		point_cnts.push_back(4);

	int m = n;
	for (int d = 2; d * d <= m; d++) {
		if (m % d != 0)
			continue;
		while (m % d == 0)
			m /= d;
		if (d >= 3)
			point_cnts.push_back(d);
	}
	if (m >= 3)
		point_cnts.push_back(m);
	for (auto p : point_cnts) {
		int edge_cnt = n / p;
		vector<int> cnt(n, 0);
		for (int i = 0; i < min(edge_cnt, n); i++) {
			cnt[i] = a[i];
			if (cnt[i] == p) {
				return true;
			}
		}
		for (int i = edge_cnt; i < n; i++) {
			cnt[i] += a[i] + cnt[i - edge_cnt];
			if (cnt[i] == p) {
				return true;
			}
		}
	}

	return false;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	if (solve())
		cout << "YES\n";
	else
		cout << "NO\n";
}
