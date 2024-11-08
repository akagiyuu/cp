#include <bits/stdc++.h>

typedef unsigned long long ll;

const ll MOD = 1000000007;

using namespace std;

ll pow(ll a, ll b, ll n)
{
	ll result = 1;
	while (b > 0) {
		if (b & 1) {
			result *= a;
			result %= n;
		}
		b /= 2;
		a *= a;
		a %= n;
	}
	return result;
}

bool sub_miller_rabin(ll a, ll n, ll s, ll d)
{
	ll p = pow(a, d, n);
	if (p == 1 || p == n - 1) {
		return false;
	}
	for (ll i = 1; i < s; i++) {
		p *= p;
		p %= n;
		if (p == n - 1) {
			return false;
		}
	}
	return true;
}

bool miller_rabin(ll n)
{
	ll s = 0;
	ll d = n - 1;
	while ((d & 1) == 0) {
		d >>= 1;
		s++;
	}
	for (ll a : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
		if (n == a) {
			return true;
		}
		if (sub_miller_rabin(a, n, s, d)) {
			return false;
		}
	}
	return true;
}

bool is_prime(ll n)
{
	for (ll i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

void solve()
{
	ll n;
	cin >> n;
	cout << (miller_rabin(n) ? "YES" : "NO") << "\n";
}

int main()
{
	for (ll i = 2; i < 1000000000; i++) {
		if (is_prime(i) != miller_rabin(i)) {
			cout << i << "\n";
		}
	}
}
