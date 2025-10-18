#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll binpow(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

ll inv(ll a)
{
	return binpow(a, MOD - 2);
}

vector<pair<ll, ll> > factorize(ll n)
{
	vector<pair<ll, ll> > res;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i != 0)
			continue;
		ll count = 0;
		while (n % i == 0) {
			count++;
			n /= i;
		}
		res.push_back(make_pair(i, count));
	}
	if (n > 1)
		res.push_back(make_pair(n, 1));
	return res;
}

ll cal(ll p, ll a, ll k)
{
	vector<ll> dp(a + 1);
	ll tmp = 1;
	for (ll i = 0; i <= a; i++) {
		dp[i] = tmp;
		tmp *= p;
	}
	// cpp_dump(dp);
	for (ll step = 0; step < k; step++) {
		vector<ll> ndp(a + 1);
		ll pre = 0;
		for (ll i = 0; i <= a; i++) {
			pre = (pre + dp[i]) % MOD;
			ndp[i] = (pre * inv(i + 1)) % MOD;
		}
		dp = ndp;
		// cpp_dump(dp);
	}
	return dp[a];
}

void solve()
{
	ll n, k;
	cin >> n >> k;

	auto f = factorize(n);
	ll res = 1;
	// cpp_dump(f);
	for (ll i = 0; i < f.size(); i++) {
		res = (res * cal(f[i].first, f[i].second, k)) % MOD;
	}
	cout << res << "\n";
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
