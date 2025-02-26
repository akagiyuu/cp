#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
constexpr ll N = 1e5;

array<ll, N + 1> build_sieve()
{
	array<ll, N + 1> sieve;
	sieve.fill(0);
	vector<ll> ps;
	for (ll i = 2; i <= N; i++) {
		if (sieve[i] == 0) {
			sieve[i] = i;
			ps.push_back(i);
		}
		for (auto p : ps) {
			ll next = p * i;
			if (next > N)
				break;
			sieve[next] = p;
			if (p == sieve[i])
				break;
		}
	}
	return sieve;
}
const array<ll, N + 1> sieve = build_sieve();

array<ll, N + 1> build_prime_count()
{
	array<ll, N + 1> pc;
	for (ll i = 2; i <= N; i++) {
		ll x = i;
		ll count = 0;
		while (x > 1) {
			ll factor = sieve[x];
			while (x % factor == 0)
				x /= factor;
			count++;
			count %= 2;
		}
		pc[i] = count;
	}
	return pc;
}

const array<ll, N + 1> pc = build_prime_count();

ll nC4(ll n)
{
	if (n < 4)
		return 0;
	return n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4;
}

void solve(ll n)
{
	ll x;
	unordered_map<ll, ll> m;
	for (ll i = 0; i < n; i++) {
		cin >> x;
		ll divisor = 1;
		while (x > 1) {
			ll fact = sieve[x];
			while (x % fact == 0)
				x /= fact;
			divisor *= fact;
			m[divisor]++;
		}
	}
	ll res = 0;
	for (auto [divisor, count] : m) {
		if (pc[divisor] % 2 == 1) {
			res += nC4(count);
		} else {
			res -= nC4(count);
		}
	}
	res = nC4(n) - res;
	cout << res << "\n";
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll n;
	while (cin >> n) {
		solve(n);
	}
}
