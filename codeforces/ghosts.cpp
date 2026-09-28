#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>

void solve()
{
	int n, a, b;
	cin >> n >> a >> b;
	map<__int128, int> cnt;
	map<pi, int> cnt_v;
	for (int i = 0; i < n; i++) {
		int x, vx, vy;
		cin >> x >> vx >> vy;
		cnt[(__int128)a * (__int128)vx - (__int128)vy]++;
		cnt_v[{ vx, vy }]++;
	}
	__int128 res = 0;
	for (auto [_, v] : cnt) {
		res += (__int128)v * (__int128)(v - 1);
	}
	for (auto [_, v] : cnt_v) {
		res -= (__int128)v * (__int128)(v - 1);
	}
	cout << (int)res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
