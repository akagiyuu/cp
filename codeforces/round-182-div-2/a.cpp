#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<ll> p(n);
	p[0] = a[0];
	for (ll i = 1; i < n; i++) {
		p[i] = p[i - 1] + a[i];
	}

	auto cal = [p](ll a, ll b) {
		if (a == 0)
			return p[b];

		return p[b] - p[a - 1];
	};
	auto ok = [p, cal, n](ll l, ll r) {
		ll a = cal(0, l) % 3;
		ll b = cal(l + 1, r) % 3;
		ll c = cal(r + 1, n - 1) % 3;

		if (a == b && b == c)
			return true;
		if (a != b && b != c && c != a)
			return true;

		return false;
	};

	for (ll l = 0; l < n; l++) {
		for (ll r = l + 1; r < n; r++) {
			if (ok(l, r)) {
				cout << l + 1 << " " << r + 1 << "\n";
				return;
			}
		}
	}

    cout << "0 0\n";
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
