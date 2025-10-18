#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll binpower(ll base, ll e, ll mod)
{
	ll result = 1;
	base %= mod;
	while (e) {
		if (e & 1)
			result = (__int128)result * base % mod;
		base = (__int128)base * base % mod;
		e >>= 1;
	}
	return result;
}

bool check_composite(ll n, ll a, ll d, int s)
{
	ll x = binpower(a, d, n);
	if (x == 1 || x == n - 1)
		return false;
	for (int r = 1; r < s; r++) {
		x = (__int128)x * x % n;
		if (x == n - 1)
			return false;
	}
	return true;
};

bool is_prime(ll n)
{
	if (n < 2)
		return false;

	int r = 0;
	ll d = n - 1;
	while ((d & 1) == 0) {
		d >>= 1;
		r++;
	}

	for (int a : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
		if (n == a)
			return true;
		if (check_composite(n, a, d, r))
			return false;
	}
	return true;
}

ll solve()
{
	ll n;
	cin >> n;
	if (n == 2)
		return 1;
	if (n == 3)
		return 1;
	if (n == 4)
		return 2;
	if (is_prime(n))
		return 1;
	if (n % 2 == 0)
		return 2;
	if (is_prime(n - 2))
		return 2;
	return 3;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
