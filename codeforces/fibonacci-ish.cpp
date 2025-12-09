#include <bits/stdc++.h>

#define int long long
#define pi pair<int, int>

using namespace std;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	unordered_map<int, int> mp, cnt;
	mp.reserve(n * 2);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		mp[a[i]]++;
	}
	int res = 2;
	vector<int> b;
	b.reserve(mp.size());
	for (auto [x, y] : mp) {
		b.push_back(x);
		if (y >= 2) {
			if (x == 0) {
				res = max(res, mp[0]);
				continue;
			}
			int cur = 2;
			int u = x;
			int v = x;
			cnt.clear();
			cnt[u]++;
			cnt[v]++;
			while (true) {
				if ((v > 0 && u > LLONG_MAX - v) || (v < 0 && u < LLONG_MIN - v))
					break;
				int z = u + v;
				auto it = mp.find(z);
				if (it == mp.end() || it->second <= cnt[z])
					break;
				cur++;
				cnt[z]++;
				u = v;
				v = z;
			}
			res = max(res, cur);
		}
	}
	n = (int)b.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				continue;
			if (b[i] == 0 && b[j] == 0) {
				res = max(res, mp[0]);
				continue;
			}
			int cur = 2;
			int x = b[i];
			int y = b[j];
			cnt.clear();
			cnt[x]++;
			cnt[y]++;
			while (true) {
				// overflow check for x + y
				if ((y > 0 && x > LLONG_MAX - y) || (y < 0 && x < LLONG_MIN - y))
					break;
				int z = x + y;
				auto it = mp.find(z);
				if (it == mp.end() || it->second <= cnt[z])
					break;
				cur++;
				cnt[z]++;
				x = y;
				y = z;
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
