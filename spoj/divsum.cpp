#include <bits/stdc++.h>

typedef unsigned long long ll;

const ll MOD = 1000000007;

using namespace std;

const ll N = 1e8;

vector<ll> build()
{
	vector<bool> is_prime(N / 2 + 1, true);
	vector<ll> ps;
	ps.push_back(2);
	for (ll i = 3; i <= N; i += 2) {
		if (!is_prime[i / 2]) {
			continue;
		}
		ps.push_back(i);
		for (ll j = i; j <= N; j += (i << 1)) {
			is_prime[j / 2] = false;
		}
	}
	return ps;
}

void solve(vector<ll> &ps)
{
	ll n;
	cin >> n;
	ll tmp = n;
	if (n == 1) {
		cout << 0 << "\n";
		return;
	}
	ll res = 1;
	for (auto p : ps) {
		if (n % p != 0) {
			continue;
		}
		ll count = 0;
		while (n % p == 0) {
			n /= p;
			count++;
		}
		res *= (pow(p, count + 1) - 1) / (p - 1);
		if (n == 1) {
			break;
		}
	}
	res -= tmp;
	cout << res << "\n";
}

int main()
{
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
	// cout.tie(NULL);

	vector<ll> ps = build();

	ll t;
	cin >> t;
	while (t--)
		solve(ps);
}
