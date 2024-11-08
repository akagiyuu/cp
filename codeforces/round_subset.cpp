#include <bits/stdc++.h>
#include "/home/yuu/Code/competitive_programming/cpp-dump/cpp-dump.hpp"

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

tuple<int, int> cal(ll n)
{
	ll temp = n;
	ll count_two = 0;
	while (temp > 0) {
		count_two++;
		temp /= 2;
	}

	temp = n;
	ll count_five = 0;
	while (temp > 0) {
		count_five++;
		temp /= 5;
	}

	return make_tuple(count_two, count_five);
}

int zero_count(tuple<int, int> metric)
{
	return min(get<0>(metric), get<1>(metric));
}

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<tuple<int, int> > metrics(n);
	for (int i = 0; i < n; i++) {
		ll x;
		cin >> x;
		metrics[i] = cal(x);
	}

	vector<vector<tuple<int, int> > > dp(k + 1, vector<tuple<int, int> >(n, make_tuple(INT_MIN, INT_MIN)));
	for (int i = 1; i <= k; i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j] = dp[i][j - 1];
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
