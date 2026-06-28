#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 5;

bool is_superior(const array<int, N> &a, const array<int, N> &b)
{
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		cnt += a[i] < b[i];
	}
	return cnt >= 3;
}

void solve()
{
	int n;
	cin >> n;

	vector<array<int, N> > a(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < N; j++) {
			cin >> a[i][j];
		}
	}

	int res = 0;
	for (int i = 1; i < n; i++) {
		if (is_superior(a[i], a[res]))
			res = i;
	}

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		cnt += is_superior(a[res], a[i]);
	}
	if (cnt == n - 1) {
		cout << res + 1 << "\n";
	} else {
		cout << -1 << "\n";
	}
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
