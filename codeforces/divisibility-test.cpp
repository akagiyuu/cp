#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e6 + 5;
const ll INF = 1e9;

ll lp[N];

void build()
{
	vector<ll> pr;

	for (ll i = 2; i < N; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (ll j = 0; i * pr[j] < N; j++) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i])
				break;
		}
	}
}

ll phi(ll n)
{
	ll res = n;

	while (n > 1) {
		ll p = lp[n];
		res = res - res / p;
		while (n % p == 0)
			n /= p;
	}

	return res;
}

ll pow(ll a, ll b, ll m)
{
	ll res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % m;
		}

		a = a * a % m;
		b >>= 1;
	}
	return res;
}

map<ll, ll> factorize(ll n)
{
	map<ll, ll> res;

	while (n > 1) {
		ll p = lp[n];
		ll cnt = 0;
		while (n % p == 0) {
			n /= p;
			cnt++;
		}
		res[p] = cnt;
	}

	return res;
}

void solve()
{
	ll b, n;
	cin >> b >> n;

	ll t1 = 1;
	auto fb = factorize(b), fn = factorize(n);
	for (auto [pn, cn] : fn) {
		ll cb = fb[pn];
		if (cb == 0) {
			t1 = INF;
			break;
		}
		ll required = (cn + cb - 1) / cb;
		t1 = lcm(t1, required);
	}

	ll t2 = INF, t3 = INF;
	if (gcd(b, n) == 1) {
		ll p = phi(n);
		t2 = p;
		for (ll i = 1; i < p; i++) {
			if (p % i != 0)
				continue;
			ll cur = pow(b, i, n);
			if (cur == 1) {
				t2 = i;
				break;
			}
			if (cur == n - 1) {
				t3 = i;
				break;
			}
		}
	}

	ll res = min(t1, min(t2, t3));
	if (res == INF) {
		cout << 0 << "\n";
		return;
	}

	if (res == t1) {
		cout << 1;
	} else if (res == t2) {
		cout << 2;
	} else if (res == t3) {
		cout << 3;
	}
	cout << " " << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--)
		solve();
}
