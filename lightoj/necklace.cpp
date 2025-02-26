#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e4;

ll phi_sieve[N + 1];
ll linear_sieve[N + 1];

void build()
{
	for (ll i = 1; i <= N; i++) {
		phi_sieve[i] = i;
	}
	for (ll i = 2; i <= N; i++) {
		if (phi_sieve[i] != i) {
			continue;
		}
		for (ll j = i; j <= N; j += i) {
			phi_sieve[j] -= phi_sieve[j] / i;
		}
	}

	for (ll i = 0; i <= N; i++) {
		linear_sieve[i] = 0;
	}
	vector<ll> ps;
	for (ll i = 2; i <= N; i++) {
		if (linear_sieve[i] == 0) {
			linear_sieve[i] = i;
			ps.push_back(i);
		}
		for (auto p : ps) {
			ll next = i * p;
			if (next > N)
				break;
			linear_sieve[next] = p;
			if (p == linear_sieve[i])
				break;
		}
	}
}

ll powmod(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = res * a % MOD;

		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

ll solve()
{
	ll n, k;
	cin >> n >> k;
	ll res = 0;
	ll gcd = n;
	ll inv_n = powmod(n, MOD - 2);
	// unordered_map<ll, ll> gcds;
	// for (ll i = 0; i < n; i++) {
	// 	gcds[gcd(n, i)]++;
	// }
	// for (auto [gcd, count] : gcds) {
	// 	if (count > 0) {
	// 		res = (res + powmod(k, gcd) % MOD * count % MOD) % MOD;
	// 	}
	// }
	while (gcd >= 1) {
		ll count = phi_sieve[n / gcd] % MOD;
		res = (res + powmod(k, gcd) % MOD * count % MOD) % MOD;
		if (gcd == 1)
			break;
		gcd /= linear_sieve[gcd];
	}
	res = res * inv_n % MOD;
    if(res < 0) res = MOD - res;
	return res;
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	int t;
	cin >> t;
	for (ll i = 1; i <= t; i++) {
		cout << "Case " << i << ": " << solve() << "\n";
	}
}
