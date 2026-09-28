#include <bits/stdc++.h>

using namespace std;

#define int long long
#define int128 __int128

int solve()
{
	int r;
	cin >> r;
	int s = floor(sqrt(r));
	int128 res = 0;

	vector<int> v;
	for (int l = 1; l <= r;) {
		int128 q = r / l;
		l = r / q + 1;
		v.push_back(q);
	}
	vector<int> pr;
	unordered_map<int, int128> g;
	for (auto x : v)
		g[x] = (int128)x * (x + 1) / 2 - 1;
	for (int p = 2; p <= s; p++) {
		if (g[p] == g[p - 1])
			continue;
		pr.push_back(p);
		res -= s * p;
		for (auto x : v) {
			if (x < p * p)
				break;
			g[x] -= (int128)p * (g[x / p] - g[p - 1]);
		}
	}
	for (int k = 1; k <= s; k++)
		res += g[r / k];

	reverse(v.begin(), v.end());
	unordered_map<int, int128> f;
	for (auto x : v)
		f[x] = 1;
	for (auto p : pr) {
		for (auto x : v)
			f[x] += f[x / p];
		res += (int128)p * f[r / p];
	}

	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << '\n';
}
