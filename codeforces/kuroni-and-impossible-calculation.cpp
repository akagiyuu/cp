#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve()
{
	ll n, m;
	cin >> n >> m;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (n > m) {
		cout << 0 << "\n";
		return;
	}

	ll p = 1;
	for (ll i = 0; i < n; i++) {
		for (ll j = i + 1; j < n; j++) {
			p = p * abs(a[j] - a[i]) % m;
		}
	}
	cout << p << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
