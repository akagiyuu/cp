#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve()
{
	int n, q;
	cin >> n >> q;
	vector<double> a(n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[i] = x;
	}
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int l1, r1, l2, r2;
			cin >> l1 >> r1 >> l2 >> r2;
			l1--;
			r1--;
			l2--;
			r2--;

			double s1 = 0;
			for (int i = l1; i <= r1; i++)
				s1 += a[i];
			s1 /= (double)(r1 - l1 + 1) * (r2 - l2 + 1);
			double s2 = 0;
			for (int i = l2; i <= r2; i++)
				s2 += a[i];
			s2 /= (double)(r1 - l1 + 1) * (r2 - l2 + 1);

			if (l1 == r1) {
				a[l1] = s2;
			} else {
				for (int i = l1; i <= r1; i++)
					a[i] = a[i] / (double)(r1 - l1 + 1) + s2;
			}

			if (l2 == r2) {
				a[l2] = s1;
			} else {
				for (int i = l2; i <= r2; i++)
					a[i] = a[i] / (double)(r2 - l2 + 1) + s1;
			}
		} else {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			double res = 0;
			for (int i = l; i <= r; i++)
				res += a[i];
			cout << fixed << setprecision(10) << res << '\n';
		}
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
