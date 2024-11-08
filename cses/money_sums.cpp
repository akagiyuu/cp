#include <bits/stdc++.h>
// #include "/home/yuu/Code/competitive_programming/cpp-dump/cpp-dump.hpp"

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	int n;
	cin >> n;
	set<ll> sums;
    sums.clear();
	for (int i = 0; i < n; i++) {
		ll x;
		cin >> x;
		set<ll> temp = sums;
		for (auto sum : temp) {
			sums.insert(sum + x);
		}
		sums.insert(x);
	}
	cout << sums.size() << "\n";
	for (auto sum : sums) {
		cout << sum << " ";
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
