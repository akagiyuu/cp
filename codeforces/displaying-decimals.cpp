#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 1;
const int MOD = 998244353;

int M[N], phi[N], cnt_pw2[N], cnt_pw5[N], cached[N];

vector<int> divisors[N];

void build()
{
	M[1] = 1;
	for (int i = 1; i < N; i++) {
		for (int j = 2 * i; j < N; j += i) {
			M[j] -= M[i];
		}
	}

	for (int i = 1; i < N; i++) {
		for (int j = i; j < N; j += i) {
			divisors[j].push_back(i);
		}
	}

	phi[1] = 0;
	for (int i = 2; i < N; i++) {
		phi[i] = i;
	}
	for (int i = 2; i < N; i++) {
		if (phi[i] != i)
			continue;
		for (int j = i; j < N; j += i) {
			phi[j] -= phi[j] / i;
		}
	}
	for (int i = 1; i < N; i++) {
		if (i % 2 == 0)
			cnt_pw2[i] = cnt_pw2[i / 2] + 1;
		if (i % 5 == 0)
			cnt_pw5[i] = cnt_pw5[i / 5] + 1;
	}
}

int binpow(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1)
			res *= a;
		a *= a;
		b >>= 1;
	}
	return res;
}

int binpow(int a, int b, int mod)
{
	int res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

int add(int a, int b)
{
	int res = a + b;
	return res > MOD ? res - MOD : res;
}

int sub(int a, int b)
{
	int res = a - b;
	return res < 0 ? res + MOD : res;
}

int count_digit(int x)
{
	if (x < 10)
		return 1;
	if (x < 100)
		return 2;
	if (x < 1000)
		return 3;
	if (x < 10000)
		return 4;
	if (x < 100000)
		return 5;
	return 6;
}

int count_fraction(int q)
{
	if (cached[q] != 0) {
		return cached[q];
	}
	int orig = q;
	int a = cnt_pw2[q], b = cnt_pw5[q];
	int res = max(a, b);
	q /= binpow(2, a);
	q /= binpow(5, b);

	int ord = phi[q];
	for (auto d : divisors[ord]) {
		if (binpow(10, d, q) == 1) {
			res = add(res, d);
			break;
		}
	}
	cached[orig] = res;
	return res;
}

int sum_integer(const vector<int> &a)
{
	auto [m, M] = minmax_element(a.begin(), a.end());
	int min = *m;
	int max = *M;
	int n = a.size();
	vector<int> cnt(max + 2, 0);
	for (int i = 0; i < n; i++) {
		cnt[a[i] + 1] += 1;
	}
	for (int i = 1; i < max + 2; i++) {
		cnt[i] = add(cnt[i], cnt[i - 1]);
	}
	auto calc_cnt = [&](int x) {
		x = std::min(x, max + 1);
		return cnt[x];
	};

	int bound = max / min;
	int x = 0;
	int dig = 1;
	int res = 0;
	while (x <= bound) {
		int next_x;
		if (x == 0)
			next_x = 10;
		else
			next_x = 10 * x;
		next_x = std::min(next_x, bound + 1);
		for (int i = 0; i < n; i++) {
			int cur = dig * sub(calc_cnt(next_x * a[i]), calc_cnt(x * a[i])) % MOD;
			res = add(res, cur);
		}

		x = next_x;
		dig++;
	}

	return res;
}

int sum_fraction(const vector<int> &a)
{
	int n = a.size();
	int max = *max_element(a.begin(), a.end());
	vector<int> cnt(max + 1), cnt_multiple(max + 1), cache_q(max + 1);
	for (int i = 0; i < n; i++) {
		cnt[a[i]]++;
		for (auto d : divisors[a[i]]) {
			cnt_multiple[d]++;
		}
	}
	int res = 0;
	for (int y = 0; y <= max; y++) {
		if (cnt[y] == 0)
			continue;
		for (auto q : divisors[y]) {
			for (auto d : divisors[q]) {
				int cur = cnt[y] * count_fraction(q) % MOD;
				cur = cur * M[d] % MOD;
				cur = (cur + MOD) % MOD;
				cur = (cur * cnt_multiple[y * d / q]) % MOD;
				res = add(res, cur);
			}
		}
	}
	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int res = sum_integer(a) + sum_fraction(a);
	int inv = binpow(a.size(), MOD - 2, MOD);
	res = res * inv % MOD * inv % MOD;
	cout << res << "\n";
}
signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
