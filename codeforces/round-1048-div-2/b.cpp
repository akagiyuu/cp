#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, m;
	cin >> n >> m;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
    sort(a.begin(), a.end());

	if (m <= n) {
		ll res = 0;
		ll offset = n - m;
		for (ll i = offset; i < n; i++) {
			res += (i + 1 - offset) * a[i];
		}
		cout << res << "\n";
		return;
	}

	ll res = 0;
	ll offset = m - n;
	for (ll i = 0; i < n; i++) {
		res += (i + 1 + offset) * a[i];
	}
	cout << res << "\n";
	return;
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
