#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int l, r, m;
	cin >> l >> r >> m;
	for (int a = l; a <= r; a++) {
		for (auto x : { m % a, m % a - a, -m % a, a - m % a }) {
			int cl = max(l - x, l);
			int cr = min(r - x, r);
			if (cl > cr)
				continue;
			int c = cl;

			int b = c + x;
			if (b < l || b > r)
				continue;

			int n = (m - (b - c)) / a;
			if (n <= 0)
				continue;

			assert(n * a + b - c == m);
			cout << a << " " << b << " " << c << "\n";
			return;
		}
	}
	assert(false);
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
