#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e7 + 7;

ll binpow(ll a, ll b)
{
	a %= MOD;
	b %= MOD - 1;

	ll res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b /= 2;
	}
	return res;
}

bool solve()
{
	ll n, k;
	cin >> n >> k;
	if (n == 0 && k == 0)
		return false;

	ll res = binpow(n, k);

	res += binpow(n - 1, k) * 2 % MOD;
	res %= MOD;

	res += binpow(n, n);
	res %= MOD;

	res += binpow(n - 1, n - 1) * 2 % MOD;
	res %= MOD;

	cout << res << "\n";

	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (solve())
		;
}
