#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const int N = 1e6;
const int PHI_N = 70;

bool is_prime[N + 1];
int pi_small[N + 1];
int phi_cache[PHI_N][100000];
vector<int> pr;

void build()
{
	fill(is_prime, is_prime + N + 1, true);
	is_prime[0] = is_prime[1] = false;

	for (int i = 2; i <= N; i++) {
		if (!is_prime[i])
			continue;
		pr.push_back(i);
		if (1LL * i * i <= N) {
			for (int j = i * i; j <= N; j += i)
				is_prime[j] = false;
		}
	}

	for (int i = 1; i <= N; i++)
		pi_small[i] = pi_small[i - 1] + is_prime[i];

	for (int x = 0; x < 100000; x++)
		phi_cache[0][x] = x;

	for (int s = 1; s < PHI_N; s++) {
		for (int x = 0; x < 100000; x++) {
			phi_cache[s][x] = phi_cache[s - 1][x] - phi_cache[s - 1][x / pr[s - 1]];
		}
	}
}

int powmod(int a, int e, int mod)
{
	int res = 1 % mod;
	while (e) {
		if (e & 1)
			res = (__int128)res * a % mod;
		a = (__int128)a * a % mod;
		e >>= 1;
	}
	return res;
}

int pow_le(int a, int e, int n)
{
	__int128 res = 1;
	for (int i = 0; i < e; i++) {
		res *= a;
		if (res > n)
			return n + 1;
	}
	return (int)res;
}

int iroot(int n, int k)
{
	if (k == 1)
		return n;

	int r = (int)pow((double)n, 1.0L / k);
	if (r < 1)
		r = 1;

	while (pow_le(r + 1, k, n) <= n)
		r++;
	while (pow_le(r, k, n) > n)
		r--;
	return r;
}

int phi(int x, int s)
{
	if (s == 0)
		return x;
	if (s == 1)
		return x - x / 2;
	if (s < PHI_N && x < 100000)
		return phi_cache[s][x];

	return phi(x, s - 1) - phi(x / pr[s - 1], s - 1);
}

int cnt_prime(int x)
{
	if (x < 2)
		return 0;
	if (x <= N)
		return pi_small[x];

	int a = cnt_prime(iroot(x, 4));
	int b = cnt_prime(iroot(x, 2));
	int c = cnt_prime(iroot(x, 3));

	int res = phi(x, a) + (b + a - 2) * (b - a + 1) / 2;
	for (int i = a; i < b; i++) {
		int w = x / pr[i];
		res -= cnt_prime(w);
		if (i < c) {
			int lim = cnt_prime(iroot(w, 2));
			for (int j = i; j < lim; j++)
				res -= cnt_prime(w / pr[j]) - j;
		}
	}

	return res;
}

int cnt_prime_pow(int x, int idx)
{
	if (x < 2)
		return 0;
	if (idx >= (int)pr.size())
		return 0;
	if (x < pr[idx])
		return 0;

	int res = max(0LL, cnt_prime(x) - idx);

	for (int e = 2;; e++) {
		int r = iroot(x, e);
		if (r < pr[idx])
			break;
		res += max(0LL, cnt_prime(r) - idx);
	}
	return res;
}

array<int, 10> calc(int x, int idx)
{
	if (x < 2)
		return {};
	if (idx >= (int)pr.size())
		return {};

	array<int, 10> res{};
	res[0] = cnt_prime_pow(x, idx);

	for (int i = idx; i + 1 < (int)pr.size(); i++) {
		int p = pr[i];
		int q = pr[i + 1];
		if ((__int128)p * q > x)
			break;

		int pe = p;
		while ((__int128)pe * q <= x) {
			auto sub = calc(x / pe, i + 1);
			for (int j = 0; j < 9; j++)
				res[j + 1] += sub[j];
			if ((__int128)pe * p > x)
				break;
			pe *= p;
		}
	}

	return res;
}

int solve()
{
	int n, mod;
	cin >> n >> mod;

	auto cnt = calc(n, 0);

	for (int k = 1; k <= 10; k++) {
		if (k % mod != 0)
			continue;

		__int128 smallest = 1;
		for (int i = 0; i < k; i++) {
			if (i >= (int)pr.size()) {
				smallest = (__int128)n + 1;
				break;
			}
			smallest *= pr[i];
			if (smallest > n)
				break;
		}

		if (smallest <= n)
			return 0;
	}

	int res = 1;

	for (int k = 1; k <= 10; k++) {
		int exp = cnt[k - 1] % (mod - 1);
		res = (int)((__int128)res * powmod(k % mod, exp, mod) % mod);
	}

	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	cout << solve() << "\n";
	return 0;
}
