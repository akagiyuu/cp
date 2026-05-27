#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e6;

ll a[N], b[N];

void build()
{
	for (ll i = 0; i <= 8; i++) {
		a[i] = 1;
		b[i] = 1;
	}
	a[9] = 1;
	b[9] = a[0] + b[0];
	for (ll i = 10; i < N; i++) {
		a[i] = (a[i - 10] + b[i - 10]) % MOD;
		b[i] = (a[i - 9] + b[i - 9]) % MOD;
	}
}

ll cnt(ll d, ll m) {
	return a[m + d];
}

void solve()
{
	ll n, m;
	cin >> n >> m;

	ll res = 0;
	while(n > 0) {
		res += cnt(n % 10, m);
		res %= MOD;
		n /= 10;
	}
	cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--)
		solve();
}
