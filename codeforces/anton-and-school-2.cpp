#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll pow(ll a, ll b)
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

const ll N = 2 * 1e6;
ll fact[N + 1];
ll ifact[N + 1];

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

ll binomial_coef(ll n, ll k)
{
	if (k > n)
		return 0;
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void solve()
{
	build();
	string s;
	cin >> s;
	ll n = s.length();
	vector<ll> right_bracket(n);
	right_bracket[n - 1] = 0;
	for (ll i = n - 2; i >= 0; i--) {
		right_bracket[i] = (s[i + 1] == ')' ? 1 : 0) + right_bracket[i + 1];
	}

	ll count = 0;
	ll cur_left_bracket = 0;
	for (ll i = 0; i < n; i++) {
		if (s[i] != '(')
			continue;
		count += binomial_coef(cur_left_bracket + right_bracket[i], cur_left_bracket + 1);
        count %= MOD;
		cur_left_bracket++;
	}
	cout << count;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
