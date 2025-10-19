#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll a, b, q;
	cin >> a >> b >> q;
	if (a > b)
		swap(a, b);

	ll p = lcm(a, b), l, r;
	while (q--) {
		cin >> l >> r;
		if (b == p) {
			cout << 0 << "\n";
			continue;
		}

		ll res = r / p - l / p + 1;
		res *= p - b;

		res -= max(l % p - b, 0ll);
		res -= min(p - 1 - r % p, p - b);
		cout << res << " ";
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
