#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll gcd(ll a, ll b, ll &x, ll &y)
{
	x = 1, y = 0;
	ll x1 = 0, y1 = 1;
	while (b) {
		ll q = a / b;
		tie(a, b) = make_pair(b, a - q * b);
		tie(x, x1) = make_pair(x1, x - q * x1);
		tie(y, y1) = make_pair(y1, y - q * y1);
	}
	return a;
}

bool solve()
{
	ll a, b, c;
	cin >> a >> b >> c;

	ll x, y;
	ll g = gcd(a, b, x, y);
	if (c % g != 0) {
		return false;
	}

	x *= c / g;
	y *= c / g;
    a /= g;
    b /= g;

	double left = (double)(-x) / (double)b;
	double right = (double)y / (double)a;

	left = ceil(left);
	right = floor(right);

	return left <= right;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	if (solve()) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
}
