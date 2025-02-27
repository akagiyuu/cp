#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

int count_substrings_divisible_by_last_digit(string s)
{
	int n = s.length();
	int count = 0;

	// // 1,2,5
	// for (int i = 0; i < n; i++) {
	// 	if (s[i] == '1' || s[i] == '2' || s[i] == '5')
	// 		count += i + 1;
	// }
	//
	// // 4
	// for (int i = 0; i < n; i++) {
	// 	if (s[i] != '4')
	// 		continue;
	// 	if (i == 0 || ((s[i - 1] - '0') * 10 + s[i] - '0') % 4 == 0) {
	// 		count += i + 1;
	// 	}
	// }

	// 3,6,9
	vector<array<int, 9> > dp(n + 1, array<int, 9>());
	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		int cur = s[i] - '0';

		for (int j = 0; j < 9; j++) {
			dp[i + 1][(j + cur) % 9] = dp[i][j];
		}
		dp[i + 1][cur % 9] += 1;

		if (cur == 3 || cur == 6) {
			count += dp[i][0] + dp[i][3] + dp[i][6];
		}
		if (cur == 9) {
			count += dp[i][0];
		}
	}
	cpp_dump(dp);

	return count;
}

void solve()
{
	string s;
	cin >> s;
	cout << count_substrings_divisible_by_last_digit(s) << "\n";
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
