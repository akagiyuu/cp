#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, l;
	cin >> n >> l;
	vector<int> a(n + 2);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	a[0] = 0;
	a[n + 1] = l;

	double x1 = 0, v1 = 1;
	int f1 = 0;

	double x2 = l, v2 = 1;
	int f2 = n + 1;

	double t = 0;
	while (x1 < x2) {
		double t1 = (a[f1 + 1] - x1) / v1;
		double t2 = (x2 - a[f2 - 1]) / v2;
		double t3 = (x2 - x1) / (v1 + v2);

		double cur = min(t1, min(t2, t3));
		// cout << x1 << " " << v1 << "\n";
		// cout << x2 << " " << v2 << "\n";
		// cout << cur << "\n\n";
		t += cur;
		x1 += cur * v1;
		x2 -= cur * v2;
		if (x1 >= a[f1 + 1]) {
			f1++;
			v1++;
		}
		if (x2 <= a[f2 - 1]) {
			f2--;
			v2++;
		}
	}
	cout << fixed << setprecision(10) << t << "\n";
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
