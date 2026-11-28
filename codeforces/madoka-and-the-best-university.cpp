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

void solve()
{
	int n;
	cin >> n;

	vector<int> mu(n + 1, 0);
	vector<vector<int> > divisors(n + 1);
	mu[1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i) {
			if (j > i)
				mu[j] = sub(mu[j], mu[i]);
			divisors[j].push_back(i);
		}
	}

	int res = 0;
	for (int c = 1; c <= n; c++) {
		for (auto g : divisors[n - c]) {
			int cur = 0;
			int s = (n - c) / g;
			for (auto d : divisors[s])
				cur = add(cur, mu[d] * sub(s / d, 1));
			cur = cur * lcm(c, g) % MOD;
			res = add(res, cur);
		}
	}
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
