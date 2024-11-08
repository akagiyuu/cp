#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

ll pow(ll a, ll b, ll m)
{
	ll res = 1;
	while (b > 0) {
		if (b & 1)
			res = res * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return res;
}

ll phi(ll n)
{
	ll res = n;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i != 0)
			continue;
		while (n % i == 0)
			n /= i;
		res -= res / i;
	}
	if (n > 1)
		res -= res / n;
	return res;
}

unordered_map<ll, ll> lhs;

ll solve()
{
	ll a, b, m;
	cin >> a >> b >> m;
	a %= m;
	b %= m;

	ll k = 1, add = 0, g;
	while ((g = gcd(a, m)) > 1) {
		if (b == k) {
			return add;
		}
		if (b % g != 0) {
			return -1;
		}
		m /= g;
		b /= g;
		add++;
		k = k * a / g % m;
	}


	ll n = sqrt(m) + 1;

	ll an = pow(a, n, m);
	ll cur = k;
	lhs.clear();
	for (ll p = 1; p <= n; p++) {
		cur = cur * an % m;
		lhs[cur] = p;
	}

	cur = b;
	for (ll q = 0; q <= n; q++) {
		if (lhs.find(cur) != lhs.end()) {
			return lhs[cur] * n - q + add;
		}
		cur = cur * a % m;
	}

	return -1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
