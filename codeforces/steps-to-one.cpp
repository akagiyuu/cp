#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

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

void solve()
{
	int m;
	cin >> m;

	vector<vector<int> > divisors(m + 1);
	for (int i = 1; i <= m; i++) {
		for (int j = i; j <= m; j += i) {
			divisors[j].push_back(i);
		}
	}
	vector<int> mu(m + 1);
	mu[1] = 1;
	for (int i = 1; i <= m; i++)
		for (int j = 2 * i; j <= m; j += i)
			mu[j] -= mu[i];

	vector<int> E(m + 1, 0);
	for (int x = 2; x <= m; x++) {
		E[x] = m;
		for (auto d : divisors[x]) {
			if (d == x)
				continue;

			int cnt = 0;
			for (int k : divisors[x / d])
				cnt = add(cnt, mu[k] * (m / d / k) % MOD);

			E[x] = add(E[x], cnt * E[d] % MOD);
		}

		E[x] = E[x] * inverse(m - m / x) % MOD;
	}
	int res = m;
	for (int x = 2; x <= m; x++)
		res = add(res, E[x]);
	res = res * inverse(m) % MOD;
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
