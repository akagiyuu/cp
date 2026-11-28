#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define ull unsigned long long

const int MOD = 998244353;

ull mulmod(ull a, ull b, ull m)
{
	return (__uint128_t)a * b % m;
}

ull powmod(ull x, ull e, ull m)
{
	ull r = 1;
	while (e) {
		if (e & 1)
			r = mulmod(r, x, m);
		x = mulmod(x, x, m);
		e >>= 1;
	}
	return r;
}
int ipow(int x, int e)
{
	int res = 1;
	while (e--)
		res = res * x;
	return res;
}
int iroot(int x, int r)
{
	int res = (int)floor(pow(x, 1. / (double)r));
	while (ipow(res + 1, r) <= x)
		res++;
	while (ipow(res, r) > x)
		res--;
	return res;
}

void solve()
{
	int n;
	cin >> n;
	unordered_map<ull, int> f;
	vector<int> a;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		bool ok = false;
		for (int r = 4; r >= 2; r--) {
			int v = iroot(x, r);
			if (ipow(v, r) == x) {
				f[v] += r;
				ok = true;
				break;
			}
		}
		if (ok)
			continue;
		a.push_back(x);
	}

	n = a.size();
	vector<bool> used(n, false);
	for (int i = 0; i < n; i++) {
		if (used[i])
			continue;
		int p = -1;
		for (int j = i + 1; j < n; j++) {
			if (used[j])
				continue;
			if (a[j] == a[i])
				continue;
			int g = __gcd(a[i], a[j]);
			if (g > 1) {
				p = g;
				break;
			}
		}
		if (p == -1)
			continue;
		f[p]++;
		f[a[i] / p]++;
		used[i] = true;
	}
	vector<int> tmp;
	for (int i = 0; i < n; i++)
		if (!used[i])
			tmp.push_back(a[i]);
	swap(a, tmp);

	bool quit = false;
	while (!quit) {
		quit = true;

		vector<ull> primes;
		for (auto [p, _] : f)
			primes.push_back(p);

		for (auto p : primes) {
			tmp.clear();
			for (auto x : a) {
				if (x % p == 0) {
					f[p]++;
					f[x / p]++;
					quit = false;
				} else
					tmp.push_back(x);
			}
			swap(a, tmp);
		}
	}

	int res = 1;
	for (auto [_, c] : f)
		res = res * (c + 1) % MOD;

	unordered_map<int, int> cnt;
	for (auto x : a)
		cnt[x]++;
	for (auto [x, c] : cnt)
		res = res * (c + 1) % MOD * (c + 1) % MOD;
	cout << res << '\n';
 }

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
