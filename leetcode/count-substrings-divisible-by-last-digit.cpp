#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

long long count_substrings_divisible_by_last_digit(string s)
{
	int n = s.length();
	long long count = 0;

	for (int i = 0; i < n; i++) {
		int cur = s[i] - '0';
		if (cur == 1 || cur == 2 || cur == 5)
			count += i + 1;
	}

	vector<array<int, 9> > dp(s.length(), array<int, 9>());

	for (int divisor : { 3, 4, 6, 7, 8, 9 }) {
		for (int i = 0; i < n; i++) {
			int cur = s[i] - '0';

			for (int j = 0; j < divisor; j++) {
				dp[i][j] = 0;
			}

			if (i > 0) {
				for (int j = 0; j < divisor; j++) {
					dp[i][(j * 10 + cur) % divisor] += dp[i - 1][j];
				}
			}

			dp[i][cur % divisor] += 1;

			if (cur == divisor) {
				count += dp[i][0];
			}
		};
	}

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
