#include <bits/stdc++.h>
// #include "/home/yuu/Code/competitive_programming/cpp-dump/cpp-dump.hpp"

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

const short digits[] = { 119, 18, 93, 91, 58, 107, 111, 82, 127, 123 };

short operation_count(short from, short to)
{
	bitset<10> a(from);
	bitset<10> b(to);
	short count = 0;
	for (short i = 0; i < 10; i++) {
		if (a[i] == 0 && b[i] == 1) {
			count += 1;
		}
		if (a[i] == 1 && b[i] == 0) {
			return -1;
		}
	}
	return count;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<short> clock(n);
	for (int i = 0; i < n; i++) {
		short cur = 0;
		for (int j = 0; j < 7; j++) {
			char tmp;
			cin >> tmp;
			cur *= 2;
			cur += tmp - '0';
		}
		clock[i] = cur;
	}
	vector<vector<short> > dp(n, vector<short>(k + 1, -1));
	for (int num = 0; num <= 9; num++) {
		short count = operation_count(clock[n - 1], digits[num]);
		if (count == -1) {
			continue;
		}
		if (count > k) {
			continue;
		}
		dp[n - 1][count] = num;
	}
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j <= k; j++) {
			for (short num = 0; num <= 9; num++) {
				short required = operation_count(clock[i], digits[num]);
				if (required == -1) {
					continue;
				}
				if (j >= required && dp[i + 1][j - required] != -1) {
					dp[i][j] = max(dp[i][j], num);
				}
			}
		}
	}
	if (dp[0][k] == -1) {
		cout << -1;
		return;
	}

	for (int i = 0; i < n; i++) {
		cout << dp[i][k] << " ";
		k -= operation_count(clock[i], digits[dp[i][k]]);
	}
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
