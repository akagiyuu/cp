#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

ll gcd(ll a, ll b, ll &x, ll &y)
{
	ll x1 = 0, y1 = 1;
	while (b != 0) {
		ll q = a / b;
		tie(x, x1) = make_tuple(x1, x - q * x1);
		tie(y, y1) = make_tuple(y1, y - q * y1);
		tie(a, b) = make_tuple(b, a - q * b);
	}
	return a;
}

ll solve()
{
	ll a, b, c, x1, x2, y1, y2;
	cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
	c = -c;

	if (a == 0 && b == 0) {
		if (c == 0)
			return (x2 - x1 + 1) * (y2 - y1 + 1);
		return 0;
	}
	if (a == 0) {
		if (c % b != 0)
			return 0;
		ll y = -c / b;
		if (y1 <= y && y <= y2) {
			return x2 - x1 + 1;
		}
		return 0;
	}
	if (b == 0) {
		if (c % a != 0)
			return 0;
		ll x = -c / a;
		if (x1 <= x && x <= x2) {
			return y2 - y1 + 1;
		}
		return 0;
	}

	ll x0 = 1, y0 = 0;
	ll g = gcd(a, b, x0, y0);
	if (c % g != 0) {
		return 0;
	}
	x0 *= c / g;
	y0 *= c / g;
	a /= g;
	b /= g;

	double nx1 = ((double)x1 - (double)x0) / (double)b;
	double nx2 = ((double)x2 - (double)x0) / (double)b;
	double ny1 = ((double)y0 - (double)y1) / (double)a;
	double ny2 = ((double)y0 - (double)y2) / (double)a;
	if (nx1 > nx2)
		swap(nx1, nx2);
	if (ny1 > ny2)
		swap(ny1, ny2);
	x1 = (ll)ceil(nx1);
	y1 = (ll)ceil(ny1);
	x2 = (ll)floor(nx2);
	y2 = (ll)floor(ny2);
	ll left = max(x1, y1);
	ll right = min(x2, y2);
	if (right - left < 0) {
		return 0;
	}
	return right - left + 1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve();
}
