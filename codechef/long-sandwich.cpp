#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e6 + 1;
int fact[N] = { 1 };

int normalize(int x, int m)
{
	x %= m;
	return x >= 0 ? x : x + m;
}
int powmod(int x, int e, int m)
{
	int r = 1;
	while (e) {
		if (e & 1)
			r = r * x % m;
		x = x * x % m;
		e >>= 1;
	}
	return r;
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
int inverse(int a, int m)
{
	a = normalize(a, m);
	int x, y;
	int g = ext_gcd(a, m, x, y);
	if (g != 1)
		return -1;
	return normalize(x, m);
}
void build_fact(int p)
{
	for (int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % p;
}

int C_prime(int n, int k, int p)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * inverse(fact[n - k] * fact[k] % p, p) % p;
}
int C_lucas(int n, int k, int p)
{
	if (k < 0 || k > n)
		return 0;
	build_fact(p);
	int res = 1;
	while (n || k) {
		int ni = n % p, ki = k % p;
		if (ki > ni)
			return 0;
		res = res * C_prime(ni, ki, p) % p;
		n /= p;
		k /= p;
	}
	return res;
}
int factorial_p_exp(int n, int p)
{
	int cnt = 0;
	for (int q = p; q <= n; q *= p)
		cnt += n / q;
	return cnt;
}

int C_prime_pow(int n, int k, int p, int p_pow, int power_count)
{
	if (k < 0 || k > n)
		return 0;
	int exp = factorial_p_exp(n, p) - factorial_p_exp(k, p) - factorial_p_exp(n - k, p);
	if (exp >= power_count)
		return 0;

	vector<int> f(p_pow + 1, 1);
	for (int i = 1; i <= p_pow; i++) {
		f[i] = f[i - 1];
		if (__gcd(i, p) == 1)
			f[i] = f[i] * i % p_pow;
	}

	auto calc_f = [&](int x) {
		int r = 1;
		if (x == 0)
			return 1LL;
		r = powmod(f[p_pow], x / p_pow, p_pow);
		r = r * f[x % p_pow] % p_pow;
		return r;
	};

	auto calc_g = [&](int x) {
		int r = 1;
		for (int cur = 1; x / cur; cur *= p)
			r = r * calc_f(x / cur) % p_pow;
		return r;
	};

	int gn = calc_g(n), gk = calc_g(k), gnk = calc_g(n - k);
	int res = gn * inverse(gnk * gk % p_pow, p_pow) % p_pow;
	return res * powmod(p, exp, p_pow) % p_pow;
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
int C(int n, int k, int m)
{
	if (k < 0 || k > n)
		return 0;
	if (m == 1)
		return 0;

	vector<int> rs, ms;
	for (int p = 2; p * p <= m; p++) {
		if (m % p != 0)
			continue;
		int p_pow = 1, cnt = 0;
		while (m % p == 0) {
			p_pow *= p;
			m /= p;
			cnt++;
		}
		int r = (p_pow == p) ? C_lucas(n, k, p) : C_prime_pow(n, k, p, p_pow, cnt);
		rs.push_back(r);
		ms.push_back(p_pow);
	}
	if (m > 1) {
		int p = m;
		int r = C_lucas(n, k, p);
		rs.push_back(r);
		ms.push_back(p);
	}

	return crt(rs, ms).first;
}

void solve()
{
	int n, k, m;
	cin >> n >> k >> m;
	int count = (n - 1) / k + 1;
	cout << count << " ";
	int res = C(count * k - n + count - 1, count - 1, m);
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
