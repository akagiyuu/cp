#include <algorithm>
#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e6;

vector<ll> prime_squares;

void get_primes()
{
	ll sieve[N + 1];
	vector<ll> ps;
	for (ll i = 2; i <= N; i++) {
		if (sieve[i] == 0) {
			sieve[i] = i;
			ps.push_back(i);
			prime_squares.push_back(i * i);
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
}

ll res, n, len;

void cal(bool is_even, ll divisor, ll start_i)
{
	for (ll i = start_i; i < len; i++) {
		if (divisor > n / prime_squares[i] + 1)
			break;
		divisor *= prime_squares[i];
		if (divisor > n)
			break;
		if (is_even) {
			res += n / divisor;
			res %= n;
		} else {
			res -= n / divisor;
			res %= n;
		}

		cal(!is_even, divisor, i + 1);
		divisor /= prime_squares[i];
	}
}

void solve()
{
	cin >> n;
	ll right = lower_bound(prime_squares.begin(), prime_squares.end(), n) - prime_squares.begin();
    cpp_dump(prime_squares[prime_squares.size() - 1]);
    cout << right << "\n";
	len = right + 1;
	res = n;

	cal(false, 1, 0);
	cout << res << "\n";
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
	// cout.tie(NULL);

	get_primes();
	int t;
	cin >> t;
	while (t--)
		solve();
}
