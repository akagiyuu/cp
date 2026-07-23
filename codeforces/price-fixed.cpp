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
	map<int, int> cnt;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		cnt[b] += a;
	}
	vector<pi> p(cnt.begin(), cnt.end());
	n = p.size();

	int s = 0;
	for (int i = 0; i < n; i++)
		s += p[i].se;

	int res = 0, bonus = 0;
	for (int i = n - 1; i >= 0; i--) {
		int cnt = s + bonus;
		int discount_cnt = min(max(cnt - p[i].fi, 0ll), p[i].se);
		res += discount_cnt + (p[i].se - discount_cnt) * 2;

		bonus += p[i].se - discount_cnt;
		s -= p[i].se;
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
