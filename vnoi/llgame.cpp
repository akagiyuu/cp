#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e5 + 1;

ll fact[N];
ll ifact[N];

ll binpow(ll a, ll b)
{
	a %= MOD;

	ll res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

void build()
{
	fact[0] = 1;
	for (ll i = 1; i < N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}

	ifact[N - 1] = binpow(fact[N - 1], MOD - 2);
	for (ll i = N - 2; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

vector<ll> mul(vector<ll> &a, vector<ll> &b)
{
	ll n = a.size();
	vector<ll> res(n, 0);

	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j <= i; j++) {
			res[i] += a[j] * b[i - j] % MOD;
			res[i] %= MOD;
		}
	}

	return res;
}

vector<ll> binpow(vector<ll> &a, ll b)
{
	ll n = a.size();
	vector<ll> res(n, 0);
	res[0] = 1;

	while (b) {
		if (b & 1)
			res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

ll solve()
{
	ll n, k, xsum = 0;
	cin >> n >> k;
	vector<ll> x(n);
	for (ll i = 0; i < n; i++) {
		cin >> x[i];
		xsum += x[i];
	}

	ll c = (k - xsum) / 2;
	if (c < 0)
		return 0;

	vector<ll> np(c + 1, 0);
	np[0] = 1;

	auto pth = [x](ll i, ll j) {
		if (x[i] + j < 0)
			return 0ll;
		return ifact[x[i] + j] * ifact[j] % MOD;
	};
	for (ll i = 0; i < n; i++) {
		for (ll j = np.size() - 1; j >= 0; j--) {
			np[j] = (np[j] * pth(i, 0)) % MOD;
			for (ll k = 0; k < j; k++) {
				np[j] += np[k] * pth(i, j - k) % MOD;
				if (pth(i, j - k) < 0) {
					return x[i] + j - k;
				}
				np[j] %= MOD;
			}
		}
	}

	ll res = 0;
	for (ll s = 0; s <= c; s++) {
		ll tmp = fact[k] * ifact[k - 2 * s - xsum] % MOD;
		tmp = (tmp * np[s]) % MOD;
		res = (res + tmp) % MOD;
	}

	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	cout << solve() << "\n";
}
