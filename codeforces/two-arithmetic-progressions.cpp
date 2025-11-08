#include <bits/stdc++.h>

#define int long long
#define double long long

using namespace std;

long long gcd(long long a, long long b, long long &x, long long &y)
{
	if (b == 0) return x = 1, y = 0, a;
	long long x1, y1;
	long long g = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return g;
}
pair<long long, long long> crt(const vector<long long> &r, const vector<long long> &m)
{
	long long r0 = 0, m0 = 1;
	for (int i = 0; i < (int)r.size(); i++) {
		long long r1 = r[i] % m[i], m1 = m[i];
		if (r1 < 0) r1 += m1;
		long long x, y;
		long long g = gcd(m0, m1, x, y);
		if ((r1 - r0) % g != 0) return { -1, 0 };
		long long lcm = m0 / g * m1;
		long long tmp = (r1 - r0) / g % (m1 / g) * x % (m1 / g);
		r0 = (r0 + m0 * tmp) % lcm;
		if (r0 < 0) r0 += lcm;
		m0 = lcm;
	}
	return { r0, m0 };
}

int solve()
{
	int a1, b1, a2, b2, l, r;
	cin >> a1 >> b1 >> a2 >> b2 >> l >> r;
	l = max(l, max(b1, b2));
	b1 %= a1;
	if (b1 < 0)
		b1 += a1;
	b2 %= a2;
	if (b2 < 0)
		b2 += a2;
	auto [x, m] = crt({ b1, b2 }, { a1, a2 });
	if (x == -1)
		return 0;
	l -= x;
	r -= x;
	int left = (int)ceil((double)l / (double)m);
	while (left * m < l)
		left++;
	int right = (int)floor((double)r / (double)m);
	while (right * m > r)
		right--;
	return max(right - left + 1, 0ll);
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
