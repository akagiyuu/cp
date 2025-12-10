#include <bits/stdc++.h>

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

using namespace std;

typedef complex<int> P;
struct L : public vector<P> {
	L(const P &a, const P &b)
	{
		push_back(a);
		push_back(b);
	}
	L()
	{
	}
};

int cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}
int dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}
int ccw(P a, P b, P c)
{
	b -= a;
	c -= a;
	if (cross(b, c) > 0)
		return +1;
	if (cross(b, c) < 0)
		return -1;
	if (dot(b, c) < 0)
		return +2;
	if (norm(b) < norm(c))
		return -2;
	return 0;
}
bool intersect(const L &s, const L &t)
{
	return ccw(s[0], s[1], t[0]) * ccw(s[0], s[1], t[1]) <= 0 && ccw(t[0], t[1], s[0]) * ccw(t[0], t[1], s[1]) <= 0;
}

int ext_gcd(int a, int b, int &x, int &y)
{
	x = 1, y = 0;
	int x1 = 0, y1 = 1;
	while (b) {
		int q = a / b;
		tie(a, b) = make_pair(b, a % b);
		tie(x, x1) = make_pair(x1, x - q * x1);
		tie(y, y1) = make_pair(y1, y - q * y1);
	}
	return a;
}

pi crt(const vector<int> &r, const vector<int> &m)
{
	int r0 = 0, m0 = 1;
	for (int i = 0; i < (int)r.size(); i++) {
		int r1 = r[i] % m[i], m1 = m[i];
		if (r1 < 0)
			r1 += m1;
		int x, y;
		int g = ext_gcd(m0, m1, x, y);
		if ((r1 - r0) % g != 0)
			return { -1, 0 };
		int lcm = m0 / g * m1;
		int tmp = (r1 - r0) / g % (m1 / g) * x % (m1 / g);
		r0 = (r0 + m0 * tmp) % lcm;
		if (r0 < 0)
			r0 += lcm;
		m0 = lcm;
	}
	return { r0, m0 };
}

int inv(int a, int m)
{
	int x, y;
	int g = ext_gcd(a, m, x, y);
	if (g != 1)
		return -1;

	x %= m;
	if (x < 0)
		x += m;
	return x;
}

pi ext_crt(const vector<int> &a, const vector<int> &b, const vector<int> &m)
{
	int n = a.size();

	vector<int> r, M;
	r.reserve(n);
	M.reserve(n);
	for (int i = 0; i < n; i++) {
		if (a[i] == 0 && b[i] == 0)
			continue;
		int g = gcd(a[i], m[i]);
		if (g == 0 || b[i] % g != 0)
			return { -1, 0 };
		int x = a[i] / g;
		int y = b[i] / g;
		int z = m[i] / g;
		r.push_back(inv(x, z) * y % z);
		M.push_back(z);
	}

	return crt(r, M);
}

int solve()
{
	int n, x, y, vx, vy;
	cin >> n >> x >> y >> vx >> vy;
	int g = gcd(vx, vy);
	vx /= g;
	vy /= g;

	auto [t, mod] = ext_crt({ vx % n, vy % n }, { (n - x % n) % n, (n - y % n) % n }, { n, n });
	if (mod == 0)
		return -1;

	int a = (x + t * vx) / n;
	int b = (y + t * vy) / n;
	// cout << a << " " << b << "\n";
	L path(P(x, y), P(a, b));
	int res = a + b - 2 + (a + b) / 2 + abs(a - b) / 2;

	bool inter_left = intersect(path, L(P(0, 0), P(0, n)));
	bool inter_down = intersect(path, L(P(0, 0), P(n, 0)));
	bool inter_hyot = intersect(path, L(P(n, 0), P(0, n)));
	if (inter_left + inter_down + inter_hyot >= 2) {
		return res;
	}
	if (inter_left || inter_down)
		res += 1;

	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
