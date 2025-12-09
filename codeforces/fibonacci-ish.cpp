#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	unordered_map<int, int> mp, cnt;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		mp[a[i]]++;
	}
	int res = 2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				continue;
			if (a[i] == 0 && a[j] == 0) {
				res = max(res, mp[0]);
				continue;
			}
			int cur = 2;
			int x = a[i];
			int y = a[j];
			cnt.clear();
			cnt[x]++;
			cnt[y]++;
			int z = x + y;
			while (mp[z] > cnt[z]) {
				cur++;
				cnt[z]++;
				x = y;
				y = z;
				z = x + y;
			}
			res = max(res, cur);
		}
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
