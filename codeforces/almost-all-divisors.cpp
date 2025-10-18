#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> d(n);
	for (ll i = 0; i < n; i++) {
		cin >> d[i];
	}
	sort(d.begin(), d.end());
	ll x = d[0] * d[d.size() - 1];

	vector<ll> d2;
	for (ll i = 2; i * i <= x; i++) {
		if (x % i != 0)
			continue;
		d2.push_back(i);
		ll i2 = x / i;
		if (i2 != i)
			d2.push_back(i2);
	}
	sort(d2.begin(), d2.end());
	if (n != d2.size()) {
		cout << "-1\n";
		return;
	}

	for (ll i = 0; i < n; i++) {
		if (d[i] != d2[i]) {
			cout << "-1\n";
			return;
		}
	}
	cout << x << "\n";
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
