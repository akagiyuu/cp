#include <bits/stdc++.h>
 #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

constexpr ll MOD = 1000000007;
constexpr ll N = 5000;

constexpr ll inv(ll b)
{
	ll a = MOD;
	b %= MOD;
	ll x = 1, y = 0, x1 = 0, y1 = 1;
	while (b) {
		ll q = a / b;
		tie(a, b) = make_pair(b, a % b);
		tie(x, x1) = make_pair(x1, x - x1 * q);
		tie(y, y1) = make_pair(y1, y - y1 * q);
	}
	return y;
}

constexpr ll powmod(ll a, ll b)
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

constexpr pair<array<ll, N + 1>, array<ll, N + 1> > build()
{
	array<ll, N + 1> fact = {};
	array<ll, N + 1> ifact = {};
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}

	ifact[N] = powmod(fact[N], MOD - 2);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
	return { fact, ifact };
}

constexpr pair<array<ll, N + 1>, array<ll, N + 1> > datas = build();

ll nCk(ll n, ll k)
{
	if (n < k)
		return 0;
	return datas.first[n] * datas.second[k] % MOD * datas.second[n - k] % MOD;
}

void solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	string compressed_s;
	compressed_s.push_back(s[0]);
	for (int i = 1; i < n; i++) {
		if (s[i] == compressed_s[compressed_s.length() - 1])
			continue;
		compressed_s.push_back(s[i]);
	}
	int m = compressed_s.length();
	vector<array<ll, 26> > dp(m + 1, { 0 });
	for (int i = 0; i < m; i++) {
		short cur = compressed_s[i] - 'a';
		dp[1][cur] = 1;
		for (int length = 2; length <= i + 1; length++) {
			dp[length][cur] = 0;
			for (short i = 0; i < 26; i++) {
				if (i == cur)
					continue;
				dp[length][cur] += dp[length - 1][i];
				dp[length][cur] %= MOD;
			}
		}
	}
	ll res = 0;
	for (int length = 1; length <= m; length++) {
		ll count = 0;
		for (short i = 0; i < 26; i++) {
			count = (count + dp[length][i]) % MOD;
		}
		res = (res + nCk(n - 1, length - 1) * count % MOD) % MOD;
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
