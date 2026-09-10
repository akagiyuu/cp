#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef unsigned long long ull;

static std::mt19937_64 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

const ull prime[] = { 2ull, 3ull, 5ull, 7ull, 11ull, 13ull, 17ull, 19ull, 23ull, 29ull, 31ull, 37ull };
const ull bases[] = { 2ull, 325ull, 9375ull, 28178ull, 450775ull, 9780504ull, 1795265022ull };

int powmod(int x, int e, int m) {
	int res = 1;
	while(e) {
		if(e & 1) res = res * x % m;
		x = x * x % m;
		e >>= 1;
	}
	return res;
}

bool is_prime(ull n)
{
	if (n < 2)
		return false;
	for (ull p : prime) {
		if (n % p == 0)
			return n == p;
	}
	ull d = n - 1;
	int s = __builtin_ctzll(d);
	d >>= s;
	auto check = [&](ull a) -> bool {
		if (a % n == 0)
			return true;
		ull x = powmod(a, d, n);
		if (x == 1 || x == n - 1)
			return true;
		for (int r = 1; r < s; ++r) {
			x = x * x % n;
			if (x == n - 1)
				return true;
		}
		return false;
	};
	for (ull a : bases) {
		if (a >= n)
			continue;
		if (!check(a))
			return false;
	}
	return true;
}
ull pollards_rho(ull n)
{
	if (n % 2 == 0)
		return 2;
	if (n % 3 == 0)
		return 3;
	std::uniform_int_distribution<ull> dist(2, n - 1);

	while (true) {
		ull y = dist(rng);
		ull c = dist(rng);
		ull m = 128; // tuning parameter
		ull g = 1, r = 1, q = 1;
		auto f = [&](ull x) -> ull { return (x * x % n + c) % n; };

		ull x, ys;
		while (g == 1) {
			x = y;
			for (ull i = 0; i < r; ++i)
				y = f(y);
			ull k = 0;
			while (k < r && g == 1) {
				ys = y;
				ull limit = min(m, r - k);
				for (ull i = 0; i < limit; ++i) {
					y = f(y);
					ull diff = x > y ? x - y : y - x;
					q = q * diff % n;
				}
				g = gcd(q, n);
				k += limit;
			}
			r <<= 1;
		}
		if (g == n) {
			do {
				ys = f(ys);
				ull diff = x > ys ? x - ys : ys - x;
				g = gcd(diff, n);
			} while (g == 1);
		}
		if (g != n && g != 0)
			return g;
	}
}
void factorize(ull n, unordered_map<ull, ull> &out)
{
	if (n == 1)
		return;
	if (is_prime(n)) {
		out[n]++;
		return;
	}
	ull d = pollards_rho(n);
	factorize(d, out);
	factorize(n / d, out);
}

pair<__int128, __int128> find(__int128 d, ull i, ull k, const vector<pair<ull, ull>> &f) {
	if(i == f.size()) {
		if(d >= k) return { -1, -1 };
		__int128 x = d + k;
		if(x & 1) return { -1, -1 };
		x >>= 1;

		__int128 q = (__int128)k * k / d;
		__int128 y = q + k;
		if(y & 1) return { -1, -1 };
		y >>= 1;

		return { x, y };
	}

	pair<__int128, __int128> res = find(d, i + 1, k, f);
	auto [p, e] = f[i];
	for(int j = 0; j < e; j++) {
		d *= p;
		if(d >= k) break;
		auto nxt = find(d, i + 1, k, f);
		if(nxt.first == -1) continue;
		if(res.first == -1) {
			res = nxt;
			continue;
		}
		if(nxt.first + nxt.second < res.first + res.second) {
			res = nxt;
		}
	}
	return res;
}

void solve()
{
	ull k;
	cin >> k;
	unordered_map<ull, ull> raw;
	factorize(k, raw);
	vector<pair<ull, ull>> f(raw.begin(), raw.end());
	for(auto &x : f) x.second <<= 1;

	auto [x, y] = find(1, 0, k, f);
	if(x == -1) cout << -1 << '\n';
	else cout << (ull)x << ' ' << (ull)y << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
