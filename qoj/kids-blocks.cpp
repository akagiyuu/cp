#include <bits/stdc++.h>

using namespace std;

#define int long long

const int INF = 1e18;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> mx_l(n);
	mx_l[0] = a[0];
	for (int i = 1; i < n; i++) {
		mx_l[i] = max(mx_l[i - 1], a[i]);
	}
	vector<int> mx_r(n);
	mx_r[n - 1] = a[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		mx_r[i] = max(mx_r[i + 1], a[i]);
	}
	int res = INF;
	for (int i = 0; i < n - 1; i++) {
		res = min(res, abs(mx_l[i] - mx_r[i + 1]));
	}
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
