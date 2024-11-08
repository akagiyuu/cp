#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

ll gcd(ll a, ll b, ll &x, ll &y)
{
	ll x1 = 0, y1 = 1;
	while (b > 0) {
		ll q = a / b;
		tie(x, x1) = make_tuple(x1, x - q * x1);
		tie(y, y1) = make_tuple(y1, y - q * y1);
		tie(a, b) = make_tuple(b, a % b);
	}
	return a;
}

bool solve()
{
	ll a, b, c, x = 1, y = 0;
	cin >> a >> b >> c;
	ll g = gcd(a, b, x, y);
	if (c % g != 0) {
		return false;
	}
	x *= c / g;
	y *= c / g;
	a /= g;
	b /= g;

	double left = (double)(-x) / (double)b;
	double right = (double)(y) / (double)a;

    ll l = ceil(left);
    ll r = floor(right);
    return r >= l;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << (solve() ? "YES" : "NO");
}
