#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MOD = 998244353;

vector<int> factor(int n)
{
	vector<int> res;

	for (int i = 2; i * i <= n; i++) {
		if (n % i != 0)
			continue;
		res.push_back(i);
		while (n % i == 0)
			n /= i;
	}
	if (n > 1)
		res.push_back(n);

	return res;
}

void count_coprime(vector<int> &f, int cur, int sign, int i, int &res, int m)
{
	int n = f.size();
	if (i == n) {
		res += sign * m / cur;
		res %= MOD;
		res = (res + MOD) % MOD;
		return;
	}
	count_coprime(f, cur, sign, i + 1, res, m);
	count_coprime(f, cur * f[i], sign * -1, i + 1, res, m);
}

int count_coprime(int n, int m)
{
	int res = 0;
	auto f = factor(n);
	count_coprime(f, 1, 1, 0, res, m);
	return res;
}

int solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int res = 1;
	for (int i = 0; i < n - 1; i++) {
		if (a[i] % a[i + 1] != 0)
			return 0;
		int cur = count_coprime(a[i] / a[i + 1], m / a[i + 1]);
		res *= cur;
		res %= MOD;
		if (res == 0)
			return 0;
	}
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
