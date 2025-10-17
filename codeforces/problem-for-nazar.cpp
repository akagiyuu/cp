#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

const ll MOD = 1000000007;

ll binpow(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b /= 2;
	}
	return res;
}

ll find_partition(ll i)
{
	for (ll k = 0; k < 64; k++) {
		if ((1ll << k) - 1ll > i) {
			return k - 1;
		}
	}

	assert(false);
}

ll find_real_value(ll i, ll k)
{
	if (k % 2 == 0) {
		return 2 * (i - 2 * ((1ll << k) - 1) / 3) + 1;
	} else {
		return 2 * (i - ((1ll << (k + 1)) - 1) / 3) + 2;
	}
}

ll sum(ll a, ll b)
{
	if (b < a)
		return 0;
	ll inv2 = binpow(2, MOD - 2);
	ll res = (b - a) % MOD;
	res = (res * inv2) % MOD;
	res = (res + 1) % MOD;
	res = res * ((b + a) % MOD) % MOD;
	res = (res * inv2) % MOD;
	return res;
}

ll solve()
{
	ll l, r;
	cin >> l >> r;
	l--;
	r--;
	if (r == 0) {
		return 1;
	}

	pair<ll, ll> odd, even;

	ll k = find_partition(l);
    // cpp_dump(k);
	odd.first = find_real_value(l, k);
	even.first = find_real_value((1ll << (k + 1)) - 1, k + 1);
	if (k % 2 == 1)
		swap(odd.first, even.first);

	k = find_partition(r);
	odd.second = find_real_value(r, k);
	even.second = find_real_value((1ll << k) - 2, k - 1);
	if (k % 2 == 1)
		swap(odd.second, even.second);
    // cpp_dump(odd, even);

	ll res = sum(odd.first, odd.second) + sum(even.first, even.second);
	res %= MOD;
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
