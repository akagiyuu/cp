#include <bits/stdc++.h>

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

using namespace std;

static inline int add(int a, int b, int m)
{
	a += b;
	return a < m ? a : a - m;
}
static inline int sub(int a, int b, int m)
{
	a -= b;
	return a < 0 ? a + m : a;
}
static inline int mul(int a, int b, int m)
{
	return (long long)a * b % m;
}

int ext_gcd(int a, int b, int &x, int &y)
{
	x = 1, y = 0;
	int x1 = 0, y1 = 1;
	while (b) {
		int q = a / b;
		tie(a, b) = make_pair(b, a - q * b);
		tie(x, x1) = make_pair(x1, x - q * x1);
		tie(y, y1) = make_pair(y1, y - q * y1);
	}
	return a;
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
		r.push_back(mul(inv(x, z), y, z));
		M.push_back(z);
	}

	return crt(r, M);
}

int solve()
{
	int n, k, w, h;
	cin >> n >> k >> w >> h;
	string s;
	cin >> s;
	w *= 2;
	h *= 2;

	map<pi, int> cnt;
	pi offset = { 0, 0 };
	for (int i = 0; i < n; i++) {
		if (s[i] == 'L') {
			offset.fi = sub(offset.fi, 1, w);
		} else if (s[i] == 'R') {
			offset.fi = add(offset.fi, 1, w);
		} else if (s[i] == 'U') {
			offset.se = add(offset.se, 1, h);
		} else {
			offset.se = sub(offset.se, 1, h);
		}
		cnt[offset] += 1;
	}
	// cout << offset.fi << " " << offset.se << "\n";

	k--;
	int res = cnt[{0, 0}];
	for (auto [y, c] : cnt) {
		auto [r, m] = ext_crt({ offset.fi, offset.se }, { sub(0, y.fi, w), sub(0, y.se, h) }, { w, h });
		if (m == 0)
			continue;
		if (r == 0)
			r = m;
		if (r > k)
			continue;
		// cout << y.fi << " " << y.se << " " << r << " " << m << "\n";
		res += ((k - r) / m + 1) * c;
	}
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
