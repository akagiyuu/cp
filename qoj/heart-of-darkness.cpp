#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 998244353;
const int N = 1e7 + 7;

int fact[N], ifact[N];

int normalize(int x)
{
	x %= MOD;
	if (x < 0)
		x += MOD;
	return x;
}
int add(int x, int y)
{
	x += y;
	if (x >= MOD)
		x -= MOD;
	return x;
}
int sub(int x, int y)
{
	x -= y;
	if (x < 0)
		x += MOD;
	return x;
}
int powmod(int x, int e)
{
	if (x == 1)
		return 1;
	if (e == 0)
		return 1;
	int r = 1;
	while (e) {
		if (e & 1)
			r = r * x % MOD;
		x = x * x % MOD;
		e >>= 1;
	}
	return r;
}
int inverse(int x)
{
	return powmod(x, MOD - 2);
}

void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % MOD;
	ifact[N - 1] = inverse(fact[N - 1]);
	for (int i = N - 2; i >= 0; i--)
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}
int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * ifact[n - k] % MOD * ifact[k] % MOD;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	k--;

	vector<int> F(n);
	F[0] = 1;
	F[1] = normalize(n + 2 * k + 1);
	for (int i = 2; i < n; i++) {
		F[i] = sub(normalize(i + 2 * k + n) * F[i - 1] % MOD, n * F[i - 2] % MOD);
		F[i] = F[i] * inverse(i) % MOD;
	}

	vector<int> P(2 * k + 3, 0), R(2 * k + 3, 0);
	P[0] = R[0] = 0;
	P[1] = R[1] = 1;
	P[2] = R[2] = sub(0, inverse(2));
	for (int c = 1; c <= k; c++) {
		vector<int> nP(2 * k + 3, 0), nR(2 * k + 3, 0);
		for (int i = 0; i < (int)P.size(); i++) {
			nP[i] = i * P[i] % MOD;
			if (i > 0)
				nP[i] = add(nP[i], normalize(2 * c - i - 1) * P[i - 1] % MOD);
		}
		for (int i = 0; i < (int)R.size(); i++) {
			nR[i] = R[i];
			if (i >= 1)
				nR[i] = sub(nR[i], 2 * R[i - 1] % MOD);
			if (i >= 2)
				nR[i] = add(nR[i], R[i - 2]);
			if (i >= c)
				nR[i] = add(nR[i], ifact[c] * nP[i - c] % MOD);
		}

		P.swap(nP);
		R.swap(nR);
	}
	vector<int> Q(2 * k + 3, 0);
	for (int i = 0; i < (int)Q.size(); i++) {
		Q[i] = sub(2 * k % MOD, i) * R[i] % MOD;
		if (i < (int)Q.size() - 1)
			Q[i] = add(Q[i], add(i, 1) * R[i + 1] % MOD);
	}

	int s_k = 0;
	for (int i = 0; i < (int)Q.size() && i < n; i++)
		s_k = add(s_k, Q[i] * F[n - 1 - i] % MOD);
	s_k = s_k * fact[n - 1] % MOD;

	int s_inf = 0;
	for (int i = 1; i <= n; i++) {
		int x = C(n - 1, i - 1) * powmod(i, i - 2) % MOD * powmod(n, n - i) % MOD;
		s_inf = add(s_inf, x);
	}

	int res = sub(s_inf, s_k);
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
