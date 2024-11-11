#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e6;

ll prime_count[N + 1];
bool sieve[N + 1];

void build()
{
	for (ll i = 2; i <= N; i++) {
		sieve[i] = true;
	}
	sieve[0] = false;
	sieve[1] = false;
	for (ll i = 2; i <= N; i++) {
		if (!sieve[i])
			continue;
		for (ll j = 2 * i; j <= N; j += i) {
			sieve[j] = false;
		}
	}
	for (ll i = 2; i <= N; i++) {
		prime_count[i] = prime_count[i - 1];
		if (sieve[i])
			prime_count[i]++;
	}
}

ll solve()
{
	ll n, k;
	cin >> n >> k;
	vector<ll> ps(k);
	for (ll i = 0; i < k; i++) {
		cin >> ps[i];
	}
	ll res = 0;
	for (ll i = 0; i <= n; i++) {
		if (sieve[i])
			continue;
		bool is_satisfy = true;
		for (ll j = 0; j < k; j++) {
			if (i % ps[j]) {
				is_satisfy = false;
				break;
			}
		}
		if (is_satisfy)
			res++;
	}
    return res;
	// ll res = n - prime_count[n] + k;
	// for (ll mask = 1; mask < (1 << k); mask++) {
	// 	ll divisor = 1;
	// 	ll count = 0;
	// 	for (ll i = 0; i < k; i++) {
	// 		if ((mask >> i) & 1) {
	// 			divisor *= ps[i];
	// 			count++;
	// 		}
	// 	}
	// 	if (count % 2 == 1) {
	// 		res -= n / divisor;
	// 	} else {
	// 		res += n / divisor;
	// 	}
	// }
	// return res;
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	ll t;
	cin >> t;
	for (ll i = 1; i <= t; i++) {
		cout << "Case " << i << ": " << solve() << "\n";
	}
}
