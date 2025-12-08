#include <bits/stdc++.h>

#define int long long
#define fi first
#define se second

using namespace std;

void solve()
{
	int n = 8;
	vector<pair<string, int> > cur(n);
	for (int i = 0; i < n; i++) {
		cin >> cur[i].fi >> cur[i].se;
	}
	for (int cnt = 0; cnt < 2; cnt++) {
		vector<pair<string, int> > next;
		for (int i = 0; i < n; i += 2) {
			if (cur[i].se > cur[i + 1].se) {
				next.push_back(cur[i]);
			} else {
				next.push_back(cur[i + 1]);
			}
		}
		cur = next;
		n /= 2;
	}
	if (cur[0].se < cur[1].se)
		swap(cur[0], cur[1]);
	cout << cur[0].fi << " beats " << cur[1].fi << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
