#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

int sum_odd_length_subarrays(vector<int> &a)
{
	int n = a.size();
    if(n == 1) {
        return a[0];
    }
	vector<int> dp(n);
	dp[0] = a[0];
	dp[1] = a[1];

	int sum = a[0] + a[1];
	int total_sum = sum;

	for (int i = 2; i < n; i++) {
		sum += a[i];
		int count = i / 2;
		dp[i] = (a[i] + a[i - 1]) * count + dp[i - 2] + a[i];
		total_sum += dp[i];
	}

	return total_sum;
}

void solve()
{
	int n;
	cin >> n;

	vector<int> a(n);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	cout << sum_odd_length_subarrays(a) << "\n";
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
