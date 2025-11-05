#include <bits/stdc++.h>

#define int long long

using namespace std;
const int N = 6;
const int MOD = 998244353;
const int NBIT = 60;

#define Matrix array<array<int, 6>, 6>

Matrix id()
{
	Matrix res;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			res[i][j] = 0;
		}
	}
	for (int i = 0; i < N; i++) {
		res[i][i] = 1;
	}

	return res;
}

Matrix mul(Matrix &a, Matrix &b)
{
	Matrix res;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			res[i][j] = 0;

			for (int k = 0; k < N; k++) {
				res[i][j] += a[i][k] * b[k][j] % MOD;
				res[i][j] %= MOD;
			}
		}
	}
	return res;
}

array<int, 6> mul(Matrix &a, array<int, 6> &b)
{
	array<int, 6> res;

	for (int i = 0; i < N; i++) {
		res[i] = 0;
		for (int j = 0; j < N; j++) {
			res[i] += a[i][j] * b[j] % MOD;
			res[i] %= MOD;
		}
	}

	return res;
}

Matrix cached[NBIT];

void build(Matrix a)
{
	cached[0] = a;
	for (int i = 1; i < NBIT; i++) {
		cached[i] = mul(cached[i - 1], cached[i - 1]);
	}
}

int binpow(int a, int b)
{
	int res = 1;

	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}

	return res;
}

Matrix init()
{
	int inv = binpow(3, MOD - 2);
	Matrix a;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			a[i][j] = 0;
		}
	}

	a[0][2] = inv;
	a[0][3] = inv;
	a[0][4] = inv;
	a[0][5] = 1;

	a[1][0] = 1;
	a[2][1] = 1;
	a[3][2] = 1;
	a[4][3] = 1;
	a[5][5] = 1;

	return a;
}

map<int, int> cached_expected;

int expected(int i)
{
	if (i == 0)
		return 0;
	if (i <= 3)
		return 1;
	int inv = binpow(3, MOD - 2);

	if (i == 4)
		return inv * 4 % MOD;

	if (cached_expected.find(i) != cached_expected.end())
		return cached_expected[i];

	array<int, 6> b = { inv * 4 % MOD, 1, 1, 1, 0, 1 };

	int pw = i - 4;
	for (int j = 0; j < NBIT; j++) {
		if ((pw >> j) & 1) {
			b = mul(cached[j], b);
		}
	}

	for (int j = 0; j < N - 1; j++) {
		cached_expected[i - j] = b[j];
	}
	return b[0];
}

void solve()
{
	int n;
	cin >> n;
	int tmp, res = 0;
	while (n--) {
		cin >> tmp;
		res = (res + expected(tmp)) % MOD;
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build(init());

	int t;
	cin >> t;
	while (t--)
		solve();
}
