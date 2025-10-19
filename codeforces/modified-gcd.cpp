#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll a, b, q;
	cin >> a >> b >> q;

	ll g = gcd(a, b);
	vector<ll> divisors;
	for (ll i = 1; i * i <= g; i++) {
		if (g % i != 0)
			continue;

		ll i2 = g / i;

		divisors.push_back(i);
		if (i2 != i)
			divisors.push_back(i2);
	}
	sort(divisors.begin(), divisors.end());
	while (q--) {
		ll l, r;
		cin >> l >> r;
		ll i = upper_bound(divisors.begin(), divisors.end(), r) - divisors.begin() - 1;
		ll x = divisors[i];
		if (x >= l) {
			cout << x << "\n";
		} else {
			cout << -1 << "\n";
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
