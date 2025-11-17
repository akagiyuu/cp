#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 20000010;
const int MAXP = 7;
const int MAXN = 50;
const int MAXM = 2 * 3 * 7 * 5 * 11 * 13 * 17;

vector<int> primes;
bitset<N> is_prime;
int prod[MAXP], pi[N], dp[MAXN][MAXM];

constexpr auto fast_div = [](const long long &a, const int &b) -> long long { return double(a) / b + 1e-9; };

void sieve()
{
	is_prime[2] = true;
	for (int i = 3; i < N; i += 2)
		is_prime[i] = true;

	for (int i = 3; i * i < N; i += 2) {
		for (int j = i * i; is_prime[i] && j < N; j += (i << 1)) {
			is_prime[j] = false;
		}
	}

	for (int i = 1; i < N; i++) {
		pi[i] = pi[i - 1] + is_prime[i];
		if (is_prime[i])
			primes.push_back(i);
	}
}

void gen()
{
	int i, j;
	assert(MAXN >= MAXP);

	sieve();
	for (prod[0] = primes[0], i = 1; i < MAXP; i++) {
		prod[i] = prod[i - 1] * primes[i];
	}

	for (i = 0; i < MAXM; i++)
		dp[0][i] = i;
	for (i = 1; i < MAXN; i++) {
		for (j = 1; j < MAXM; j++) {
			dp[i][j] = dp[i - 1][j] - dp[i - 1][fast_div(j, primes[i - 1])];
		}
	}
}

uint64_t phi(long long m, int n)
{
	if (!n)
		return m;
	if (n < MAXN && m < MAXM)
		return dp[n][m];
	if (n < MAXP)
		return dp[n][m % prod[n - 1]] + fast_div(m, prod[n - 1]) * dp[n][prod[n - 1]];

	long long p = primes[n - 1];
	if (m < N && p * p >= m)
		return pi[m] - n + 1;
	if (p * p * p < m || m >= N)
		return phi(m, n - 1) - phi(fast_div(m, p), n - 1);

	int lim = pi[(int)sqrt(0.5 + m)];
	uint64_t res = pi[m] - (lim + n - 2) * (lim - n + 1) / 2;
	for (int i = n; i < lim; i++) {
		res += pi[fast_div(m, primes[i])];
	}

	return res;
}

uint64_t lehmer(long long n)
{
	if (n < N)
		return pi[n];

	int s = sqrt(0.5 + n), c = cbrt(0.5 + n);
	uint64_t res = phi(n, pi[c]) + pi[c] - 1;
	for (int i = pi[c]; i < pi[s]; i++) {
		res -= lehmer(fast_div(n, primes[i])) - i;
	}

	return res;
}

void solve()
{
	int n;
	cin >> n;
	int res = 0;
	for (auto x : primes) {
		int y = n / x;
		if (x >= y)
			break;
		// cout << x << " " << y << "\n";
		int px = lehmer(x);
		int py = lehmer(y);
		if (py <= px)
			break;
		res += py - px;
	}
	for (auto x : primes) {
		int cur = x * x * x;
		if (cur > n)
			break;
		res += 1;
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	gen();
	solve();
}
