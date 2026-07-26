#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 1000000007;

bool solve()
{
	int n, m;
	cin >> n >> m;
	vector<pi> a(n * m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			cin >> x;
			x--;
			a[x] = { i, j };
		}
	}
	vector<vector<int> > b(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> b[i][j];
			b[i][j]--;
		}
	}

	for (int i = 0; i < n; i++) {
		int k = a[b[i][0]].fi;
		for (int j = 1; j < m; j++) {
			if (a[b[i][j]].fi != k)
				return false;
		}
	}

	for (int j = 0; j < m; j++) {
		int k = a[b[0][j]].se;
		for (int i = 1; i < n; i++) {
			if (a[b[i][j]].se != k)
				return false;
		}
	}

	return true;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		if (solve())
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}
