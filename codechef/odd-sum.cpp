#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

int solve()
{
	int n;
	cin >> n;

	return 1 + (n - 2) * (n - 1);
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
