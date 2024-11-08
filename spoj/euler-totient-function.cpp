#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

vector<ll> build(ll n)
{
	vector<ll> f(n + 1);
	for (ll i = 1; i <= n; i++) {
		f[i] = i;
	}
	for (ll i = 2; i <= n; i++) {
		if (f[i] < i) {
			continue;
		}
		for (ll j = i; j <= n; j += i) {
			f[j] -= f[j] / i;
		}
	}
	return f;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	auto f = build(1e6);

	int t;
	cin >> t;
	while (t--) {
		ll i;
		cin >> i;
		cout << f[i] << "\n";
	}
}
