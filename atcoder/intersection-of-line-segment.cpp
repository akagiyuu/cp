#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

struct pt {
	ll x;
	ll y;

	pt()
	{
	}
	pt(ll x, ll y)
	{
		this->x = x;
		this->y = y;
	}

	pt operator-(const pt &p)
	{
		return pt(x - p.x, y - p.y);
	}

	ll cross(const pt &p)
	{
		return x * p.y - y * p.x;
	}

	ll cross(pt &a, pt &b)
	{
		return (a - *this).cross(b - *this);
	}
};

bool inter1(ll a, ll b, ll c, ll d)
{
	if (a > b)
		swap(a, b);
	if (c > d)
		swap(c, d);

	return max(a, c) <= min(b, d);
}

short sgn(ll n)
{
	if (n > 0)
		return 1;
	if (n < 0)
		return -1;
	return 0;
}

bool solve()
{
	pt a, b, c, d;
	cin >> a.x >> a.y;
	cin >> b.x >> b.y;
	cin >> c.x >> c.y;
	cin >> d.x >> d.y;

	if (c.cross(d, a) == 0 && c.cross(d, b) == 0)
		return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);

	return sgn(c.cross(d, a)) != sgn(c.cross(d, b)) && sgn(a.cross(b, c)) != sgn(a.cross(b, d));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	if (solve()) {
		cout << "Yes\n";
	} else {
		cout << "No\n";
	}
}
