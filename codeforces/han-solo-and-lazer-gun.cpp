#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 1000000007;

bool same_line(pi o, pi a, pi b)
{
	return (a.fi - o.fi) * (b.se - o.se) == (a.se - o.se) * (b.fi - o.fi);
}

void solve()
{
	int n;
	pi o;
	cin >> n >> o.fi >> o.se;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].fi >> a[i].se;
	}
	vector<pi> b;
	for (int i = 0; i < n; i++) {
		int m = b.size();

		bool add = true;
		for (int j = 0; j < m; j++) {
			if (same_line(o, a[i], b[j])) {
				add = false;
				break;
			}
		}
		if (add) {
			b.push_back(a[i]);
		}
	}
	cout << b.size() << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
