#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, m;
	cin >> n >> m;
	vector<ll> a(n), b(m);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i < m; i++) {
		cin >> b[i];
	}

	ll min_a = a[0];
	for (ll i = 1; i < n; i++) {
		min_a = min(min_a, a[i]);
	}

	ll gcd_diff = 0;
	for (auto x : a) {
		gcd_diff = gcd(gcd_diff, x - min_a);
	}
	for (auto y : b) {
		ll res = gcd(y + min_a, gcd_diff);
		cout << res << " ";
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
