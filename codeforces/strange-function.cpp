#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll f(ll x)
{
	for (ll i = 1;; i++) {
		if (x % i != 0)
			return i;
	}
}

ll solve()
{
	ll n;
	cin >> n;

	ll res = 0;
	ll p = 1;
	for (ll i = 2; i <= 42; i++) {
		ll next_p = lcm(p, i);
		ll cnt = (n / p) % MOD;
		ll next_cnt = (n / next_p) % MOD;
		ll diff = (cnt - next_cnt + MOD) % MOD;

		res += diff * i % MOD;
		res %= MOD;
		p = next_p;
	}
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
