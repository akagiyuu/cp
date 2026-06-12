#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll a, b, x;
	cin >> a >> b >> x;
	vector<ll> div_a, div_b;
	while (a > 0) {
		div_a.push_back(a);
		a /= x;
	}
	div_a.push_back(a);
	while (b > 0) {
		div_b.push_back(b);
		b /= x;
	}
	div_b.push_back(b);
	ll n = div_a.size();
	ll m = div_b.size();
	ll res = 1e9;
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < m; j++) {
			res = min(res, abs(div_a[i] - div_b[j]) + i + j);
		}
	}
	cout << res << "\n";
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
