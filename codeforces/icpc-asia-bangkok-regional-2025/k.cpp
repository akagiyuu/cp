#include <bits/stdc++.h>

#define int long long

using namespace std;

int ext_gcd(int a, int b, int &x, int &y)
{
	x = 1, y = 0;
	int x0 = 0, y0 = 1;
	while (b) {
		int q = a / b;
		tie(a, b) = make_pair(b, a % b);
		tie(x, x0) = make_pair(x0, x - q * x0);
		tie(y, y0) = make_pair(y0, y - q * y0);
	}
	return a;
}

pair<int, int> crt(const vector<int> &r, const vector<int> &m)
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

// sum_{i = 0}^{n} floor(ax + b / c)
int floor_sum(int a, int b, int c, int n)
{
	if (a == 0) return (b / c) * (n + 1);
	if (a >= c or b >= c)
		return ((n * (n + 1)) / 2) * (a / c) + (n + 1) * (b / c) + floor_sum(a % c, b % c, c, n);
	int m = (a * n + b) / c;
	return m * n - floor_sum(c, c - b - 1, a, m - 1);
}

int solve()
{
	int i, j, n, m;
	cin >> i >> j >> n >> m;
	i--;
	j--;
	n--;
	m--;

	vector<int> r = { i, j }, mod = { n, m };
	for (int i = 0; i < (int)r.size(); i++) {
		r[i] = (mod[i] - r[i]) % mod[i];
	}

	auto [k, _] = crt(r, mod);
	if (k == -1)
		return -1;
	int res = k + 1;
	k -= n + m;
    if(k < 0) return res;
	int t = k / n;
	res -= (t + 1);
	res -= floor_sum(n, k - n * t, m, t);
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
