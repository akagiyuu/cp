#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

ll gcd(ll a, ll b)
{
	if (a < b)
		swap(a, b);
	while (b > 0) {
		tie(a, b) = make_pair(b, a % b);
	}
	return a;
}

ll pow(ll a, ll b, ll m)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % m;
		a = (a * a) % m;
		b >>= 1;
	}
	return res;
}

ll solve()
{
	ll a, m, b;
	cin >> a >> m >> b;
	if (a == 0 && m == 0 && b == 0) {
		return -2;
	}
	a %= m;
	b %= m;
	ll g, k = 1, add = 0;
	while ((g = gcd(a, m)) > 1) {
        if(b == k) {
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
	unordered_map<ll, ll> rhs;
	ll cur = b;
	for (ll q = 0; q <= n; q++) {
		rhs[cur] = q;
		cur = (cur * a) % m;
	}

	cur = k;
	ll an = pow(a, n, m);
	for (ll p = 1; p <= n; p++) {
		cur = (cur * an) % m;
		if (rhs.count(cur)) {
			return n * p - rhs[cur] + add;
		}
	}
	return -1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true) {
		ll v = solve();
		if (v == -2) {
			break;
		}
		if (v == -1) {
			cout << "No Solution\n";
			continue;
		}
		cout << v << "\n";
	}
}
