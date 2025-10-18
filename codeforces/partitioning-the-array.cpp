#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

bool is_possible(vector<ll> &a, ll k)
{
	ll n = a.size();
	ll m = 0;

	for (ll i = 0; i < n - k; i++) {
		m = gcd(m, abs(a[i + k] - a[i]));
		if (m == 1)
			return false;
	}

	return m != 1;
}

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	ll cnt = 0;
	for (ll i = 1; i * i <= n; i++) {
		if (n % i != 0)
			continue;
		cnt += is_possible(a, i);
		ll i2 = n / i;
		// cout << i << " " << is_possible(a, i) << "\n";
		if (i2 != i) {
			cnt += is_possible(a, i2);
			// cout << i2 << " " << is_possible(a, i2) << "\n";
		}
	}
	cout << cnt << "\n";
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
