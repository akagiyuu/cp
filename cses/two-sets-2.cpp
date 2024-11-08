#include <bits/stdc++.h>
// #include "/home/yuu/Code/competitive_programming/cpp-dump/cpp-dump.hpp"

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	int n;
	cin >> n;
	ll total_sum = n * (n + 1) / 2;
	ll s = total_sum >> 1;
	if (2 * s != total_sum) {
		cout << 0;
		return;
	}
	vector<ll> sums(s + 1, 0);
	sums[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = s - i; j >= 0; j--) {
			sums[i + j] += sums[j];
			sums[i + j] %= MOD;
		}
	}

	cout << (sums[total_sum / 2] * 500000004) % MOD;
}

int main()
{
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
	// cout.tie(NULL);
	//
	// int t;
	// cin >> t;
	// while (t--)
	solve();
}
