#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve()
{
	int n;
	cin >> n;
	int s = 0;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		s += x;
	}
	cout << max(0ll, 600 - s) << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
