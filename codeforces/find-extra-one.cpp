#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

bool solve()
{
	int n;
	cin >> n;
	int cnt_l = 0;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		cnt_l += x > 0;
	}
	return cnt_l == 1 || cnt_l == n - 1 || cnt_l == 0 || cnt_l == n;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	if(solve()) cout << "Yes\n";
	else cout << "No\n";
}
