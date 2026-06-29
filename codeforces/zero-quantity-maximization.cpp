#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	int offset = 0;
	map<pi, int> cnt;
	for (int i = 0; i < n; i++) {
		if (a[i] == 0 && b[i] == 0) {
			offset++;
			continue;
		}
		if (a[i] == 0)
			continue;
		if (b[i] == 0) {
			cnt[{ 0, 1 }]++;
			continue;
		}
		int g = gcd(abs(a[i]), abs(b[i]));
		pi cur = { a[i] / g, b[i] / g };
		if (cur.se < 0) {
			cur.fi = -cur.fi;
			cur.se = -cur.se;
		}
		cnt[cur]++;
	}
	int res = 0;
	for (auto [_, c] : cnt) {
		res = max(res, c);
	}
	cout << res + offset << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
