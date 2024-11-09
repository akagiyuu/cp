#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1e8 + 7;
const ll N = 2e6;
const ll MAX_VAL = 1e10;

ll pow(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
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

ll fact[N + 1], ifact[N + 1];
vector<ll> perfect_numbers;

vector<ll> build()
{
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	ifact[N] = powmod(fact[N], MOD - 2);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}

    set<ll> tmp;
	for (ll base = 2; base <= (ll)1e5; base++) {
		ll cur = base * base;
		while (cur <= MAX_VAL) {
			tmp.insert(cur);
			cur *= base;
		}
	}
    vector<ll> nums(tmp.begin(), tmp.end());
    return nums;
}

ll count_perfect(ll a, ll b)
{
	ll left = lower_bound(perfect_numbers.begin(), perfect_numbers.end(), a) - perfect_numbers.begin();
	ll right = upper_bound(perfect_numbers.begin(), perfect_numbers.end(), b) - perfect_numbers.begin() - 1;
    return right - left + 1;
}

ll catalan(ll n)
{
	return fact[2 * n] * ifact[n] % MOD * ifact[n + 1] % MOD;
}

void solve()
{
	ll a, b;
	cin >> a >> b;
	ll count = count_perfect(a, b);
	ll res = count == 0 ? 0 : catalan(count);
	cout << res << "\n";
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	perfect_numbers = build();
	int t;
	cin >> t;
	for (ll i = 1; i <= t; i++) {
		cout << "Case " << i << ": ";
		solve();
	}
}
