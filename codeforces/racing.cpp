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
	vector<int> d(n);
	vector<pi> b(n);
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i].fi >> b[i].se;
	}
	int l = 0, r = 0;
	for (int i = 0; i < n; i++) {
		if (d[i] == -1) {
			r++;
		}
		if (d[i] == 1) {
			l++;
			r++;
		}

		b[i].fi = max(l, b[i].fi);
		b[i].se = min(r, b[i].se);
		l = b[i].fi;
		r = b[i].se;
		if (l > r) {
			cout << -1 << "\n";
			return;
		}
	}
	b.insert(b.begin(), { 0, 0 });
	int h = b[n].se;
	for (int i = n - 1; i >= 0; i--) {
		if (d[i] != -1) {
			h -= d[i];
		} else {
			if (b[i].fi <= h && h <= b[i].se) {
				d[i] = 0;
			} else {
				h--;
				d[i] = 1;
			}
		}
	}
	// cout << "\n";
	// cout << "TEST\n";
	// for (int i = 0; i < n; i++) {
	// 	cout << b[i].fi << " " << b[i].se << "\n";
	// }
	// cout << "\n";
	for (int i = 0; i < n; i++) {
		cout << d[i] << " ";
	}
	cout << "\n";
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
