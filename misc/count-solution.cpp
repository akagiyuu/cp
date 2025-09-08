#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 50;

ll powmod(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = res * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return res;
}

ll fact[N + 1];
ll ifact[N + 1];

void build()
{
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	ifact[N] = powmod(fact[N], MOD - 2);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

ll nCk(ll n, ll k)
{
	if (n < k)
		return 0;
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void solve()
{
    ll n, k;
    cin >> n >> k;

    ll res = 0;
    for (ll i = 0; i <= n; i++) {
        ll val = (nCk(n, i) * nCk(k + n - 1 - 9 * i, n - 1)) % MOD;
        if(i % 2 == 0)
            res += val;
        else
            res -= val;
    }

    for (ll i = 0; i <= n - 1; i++) {
        ll val = (nCk(n - 1, i) * nCk(k + n - 2 - 9 * i, n - 2)) % MOD;
        if(i % 2 == 0)
            res -= val;
        else
            res += val;
    }

    cout << res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    build();
	solve();
}
