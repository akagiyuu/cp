#include <bits/stdc++.h>

#define int long long

using namespace std;

int mul_mod(int a, int b, int m)
{
	return (int)((__int128)a * b % m);
}

int pow_mod(int a, int e, int m)
{
	int r = 1;
	while (e) {
		if (e & 1)
			r = mul_mod(r, a, m);
		a = mul_mod(a, a, m);
		e >>= 1;
	}
	return r;
}

bool is_prime(int n)
{
	if (n < 2)
		return false;
	static const int small_primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
	for (int p : small_primes) {
		if (n % p == 0)
			return n == p;
	}
	int d = n - 1, s = 0;
	while ((d & 1) == 0) {
		d >>= 1;
		++s;
	}
	auto check = [&](int a) -> bool {
		if (a % n == 0)
			return true;
		int x = pow_mod(a, d, n);
		if (x == 1 || x == n - 1)
			return true;
		for (int r = 1; r < s; ++r) {
			x = mul_mod(x, x, n);
			if (x == n - 1)
				return true;
		}
		return false;
	};
	int mr_bases[] = { 2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL };
	for (int a : mr_bases)
		if (!check(a))
			return false;
	return true;
}

static std::mt19937_64 rng((uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count());

int brent_rho(int n)
{
	if (n % 2 == 0)
		return 2;
	if (n % 3 == 0)
		return 3;
	int y = std::uniform_int_distribution<int>(1, n - 1)(rng);
	int c = std::uniform_int_distribution<int>(1, n - 1)(rng);
	int m = std::uniform_int_distribution<int>(1, n - 1)(rng) % (n - 1) + 1;
	int g = 1, r = 1, q = 1;
	int x = 0, ys = 0;
	while (g == 1) {
		x = y;
		for (int i = 0; i < r; ++i)
			y = (mul_mod(y, y, n) + c) % n;
		int k = 0;
		while (k < r && g == 1) {
			ys = y;
			int lim = std::min(m, r - k);
			for (int i = 0; i < lim; ++i) {
				y = (mul_mod(y, y, n) + c) % n;
				q = mul_mod(q, (x > y) ? x - y : y - x, n);
			}
			g = std::gcd(q, n);
			k += lim;
		}
		r <<= 1;
	}
	if (g == n) {
		do {
			ys = (mul_mod(ys, ys, n) + c) % n;
			g = std::gcd((x > ys) ? x - ys : ys - x, n);
		} while (g == 1);
	}
	return g;
}

void factorize(int n, unordered_map<int, int> &out)
{
	if (n == 1)
		return;
	if (is_prime(n)) {
		out[n]++;
		return;
	}
	static const int trial_primes[] = { 2,	3,  5,	7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
					    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
	for (int p : trial_primes) {
		if (n % p == 0) {
			out[p]++;
			factorize(n / p, out);
			return;
		}
	}
	int d = n;
	while (d == n)
		d = brent_rho(n);
	factorize(d, out);
	factorize(n / d, out);
}

void solve()
{
	string s;
	cin >> s;
	int sz = s.size();
	int n = 0;
	for (int i = 0; i < min(sz, 10ll); i++) {
		n = 10 * n + s[i] - '0';
	}
	unordered_map<int, int> f;
	factorize(n, f);
	int remain = sz - 10;
	if (remain > 0) {
		f[2] += remain;
		f[5] += remain;
	}
	cout << f.size() << "\n";
	for (auto [p, pw] : f) {
		cout << p << " " << pw << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
