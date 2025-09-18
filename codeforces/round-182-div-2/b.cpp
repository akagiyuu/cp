#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	ll cz = 0;

	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] == 0) {
			cz++;
		}
	}
	if (cz == 1) {
		ll x = 1;
		for (ll i = 2; i <= n; i++) {
			x ^= i;
		}
		ll index;
		for (ll i = 0; i < n; i++) {
			if (a[i] == 0) {
				index = i;
				continue;
			}
			if (x == -1) {
				x = a[i];
			} else {
				x ^= a[i];
			}
		}
		a[index] = x;
	}

	ll l = 0;
	for (; l < n; l++) {
		if (a[l] != l + 1) {
			break;
		}
	}
	if (l == n) {
		cout << "0\n";
		return;
	}
	ll r = n - 1;
	for (; r >= 0; r--) {
		if (a[r] != r + 1) {
			break;
		}
	}
	if (cz <= 1) {
		cout << r - l + 1 << "\n";
		return;
	}

	ll lz = 0;
	for (; lz < n; lz++) {
		if (a[lz] == 0) {
			break;
		}
	}

	ll rz = n - 1;
	for (; rz >= 0; rz--) {
		if (a[rz] == 0) {
			break;
		}
	}
	ll res = max(r, rz) - min(l, lz) + 1;
	if (res == 1) {
		cout << "0\n";
	} else {
		cout << res << "\n";
	}
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
