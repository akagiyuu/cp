#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e7;

ll fact[N + 1];
ll ifact[N + 1];

ll pow(ll a, ll b)
{
	a %= MOD;
	b %= MOD - 1;
	ll res = 1;
	while (b) {
		if (b & 1)
			res = res * a % MOD;

		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

void build()
{
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	ifact[N] = pow(fact[N], MOD - 2);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

ll solve(ll n)
{
	vector<ll> diffs(n, 0);
	for (ll i = 0; i < n; i++) {
		cin >> diffs[i];
	}

	ll sum = 0;
	for (ll i = 0; i < n; i++) {
		ll tmp;
		cin >> tmp;
		diffs[i] = tmp - diffs[i];
		if (diffs[i] < 0) {
			return 0;
		}
		sum += diffs[i];
	}

	ll res = fact[sum];
	for (ll i = 0; i < n; i++) {
		res = res * ifact[diffs[i]] % MOD;
	}
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    build();
	while (true) {
		ll n;
		cin >> n;
		if (n == 0)
			break;
		cout << solve(n) << "\n";
	}
}
