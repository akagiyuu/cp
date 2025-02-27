#include <algorithm>
#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

int lenght_of_longest_fibonacci_subsequence(vector<int> &a)
{
	int n = a.size();
	vector<vector<int> > dp(n, vector<int>(n));
	int res = 0;

	for (int i = n - 2; i >= 0; i--) {
		for (int j = n - 1; j >= i + 1; j--) {
			int k = lower_bound(a.begin() + j + 1, a.end(), a[i] + a[j]) - a.begin();
			if (k == n || a[k] != a[i] + a[j]) {
				dp[i][j] = 2;
				continue;
			}
			dp[i][j] = 1 + dp[j][k];
			res = max(res, dp[i][j]);
		}
	}

	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	cout << lenght_of_longest_fibonacci_subsequence(a) << "\n";
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
