#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

bool solve()
{
	int n;
	cin >> n;
	return n % 4 == 0;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		if (solve())
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}
