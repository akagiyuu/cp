#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(m);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < m; i++)
		cin >> b[i];
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	int x = min(n / 2, m);
	int y = min(m / 2, n);
	vector<int> f(x + 1), g(y + 1);
	int l = 0, r = 0;
	for (int i = 0; i <= x; i++) {
		f[i] = r - l;
		l += a[i];
		r += a[n - 1 - i];
	}
	l = 0;
	r = 0;
	for (int i = 0; i <= y; i++) {
		g[i] = r - l;
		l += b[i];
		r += b[m - 1 - i];
	}

	int mx_k = 0;
	for (int i = 0; i <= x; i++) {
		int j = min(n - 2 * i, (m - i) / 2);
		mx_k = max(mx_k, i + j);
	}
	cout << mx_k << '\n';
	if (mx_k == 0)
		return;

	for (int k = 1; k <= mx_k; k++) {
		int l = max(k - y, max(2 * k - m, 0ll));
		int r = min(min(n - k, k), x);
		assert(l <= r);
		auto calc = [&f, &g, k](int i) { return f[i] + g[k - i]; };

		while (r - l >= 5) {
			int mid = (l + r) / 2;
			if (calc(mid) < calc(mid + 1))
				l = mid;
			else
				r = mid + 1;
		}
		for (int i = l + 1; i <= r; i++)
			if (calc(l) < calc(i))
				l = i;
		cout << calc(l) << ' ';
	}
	cout << '\n';
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
