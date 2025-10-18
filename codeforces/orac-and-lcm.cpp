#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

vector<ll> linear_sieve(ll n)
{
	vector<ll> lp(n + 1);
	vector<ll> pr;

	for (ll i = 2; i <= n; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (ll j = 0; i * pr[j] <= n; ++j) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i]) {
				break;
			}
		}
	}
	return pr;
}

ll binpow(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res *= a;
		a *= a;
		b >>= 1;
	}
	return res;
}

ll find_pow(ll x, ll p)
{
	ll cnt = 0;
	while (x % p == 0) {
		cnt++;
		x /= p;
	}
	return cnt;
}

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	auto ps = linear_sieve(2e6 + 1);
	// cout << ps.size() << "\n";

	ll res = 1;
	vector<ll> b;
	for (auto p : ps) {
		ll cnt = 0;
		bool is_valid = true;
		b.clear();
		// cout << p << "\n";
		for (auto x : a) {
			ll pw = find_pow(x, p);
			b.push_back(pw);
			if (pw == 0) {
				cnt++;
				if (cnt == 2) {
					is_valid = false;
					break;
				}
				continue;
			}

			// cout << pw << " ";
		}
		// cout << "\n";
		// cout << m2 << "\n\n";
		if (is_valid) {
			nth_element(b.begin(), b.begin() + 1, b.end());
			res *= binpow(p, b[1]);
		}
	}
	cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
