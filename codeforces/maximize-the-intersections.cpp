#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

void solve()
{
	int n, k;
	cin >> n >> k;
	set<int> s;
	for (int i = 1; i <= 2 * n; i++)
		s.insert(i);
	vector<pi> chords(k);
	for (int i = 0; i < k; i++) {
		cin >> chords[i].fi >> chords[i].se;
		if (chords[i].fi > chords[i].se)
			swap(chords[i].fi, chords[i].se);
		s.erase(chords[i].fi);
		s.erase(chords[i].se);
	}
	vector<int> remain(s.begin(), s.end());
	for (int i = 0; i < n - k; i++) {
		chords.push_back({ remain[i], remain[i + n - k] });
	}
	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			auto [a, b] = chords[i];
			auto [c, d] = chords[j];
			if (a < c && c < b && (d < a || d > b)) {
				res++;
			} else if (a < d && d < b && (c < a || c > b)) {
				res++;
			}
		}
	}
	cout << res << '\n';
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
