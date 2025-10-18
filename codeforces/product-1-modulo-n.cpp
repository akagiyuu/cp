#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll extend_gcd(ll a, ll b, ll &x, ll &y)
{
	x = 1, y = 0;
	ll x1 = 0, y1 = 1;
	while (b) {
		ll q = a / b;
		tie(a, b) = make_pair(b, a - q * b);
		tie(x, x1) = make_pair(x1, x - q * x1);
		tie(y, y1) = make_pair(y1, y - q * y1);
	}
	return a;
}

void solve()
{
	ll n;
	cin >> n;
	vector<pair<ll, ll> > a;
	ll p = 1;
	for (ll i = 1; i <= n - 1; i++) {
		ll x, y;
		if (extend_gcd(i, n, x, y) != 1)
			continue;

		ll inv = (i % n + n) % n;

		a.push_back(make_pair(i, inv));
		p = (p * i) % n;
	}
	if (p != 1) {
		ll m = a.size();
		for (ll i = 0; i < m; i++) {
			if ((p * a[i].second) % n != 1)
				continue;
			a.erase(a.begin() + i);
			break;
		}
	}
	cout << a.size() << "\n";
	for (auto [x, inv] : a) {
		cout << x << " ";
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
