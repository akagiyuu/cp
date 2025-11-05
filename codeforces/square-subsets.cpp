#include <bits/stdc++.h>

#define int long long

using namespace std;

// const int N = 71;
// vector<int> pr;
// int sieve[N];

// void build()
// {
// 	for (int i = 2; i < N; i++) {
// 		if (sieve[i])
// 			continue;
//
// 		pr.push_back(i);
// 		for (int j = 2 * i; j < N; j += i) {
// 			sieve[j] = true;
// 		}
// 	}
// }

int pr[] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
};
const int N = 19;

void solve()
{
	int n;
	cin >> n;

	unordered_map<int, int> dp, ndp;
	int x;
	while (n--) {
		cin >> x;
		ndp = dp;
		int f = 0;
		for (int i = 0; i < N; i++) {
			if (x % pr[i] != 0)
				continue;
			while (x % pr[i] == 0) {
				x /= pr[i];
				f ^= (1 << i);
			}
		}
		ndp[f]++;
		for (auto [mask, cnt] : dp) {
			ndp[f ^ mask] += cnt;
		}
		dp = ndp;
	}
	cout << dp[0] << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
