#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	int cnt = 0;
	string s;
	while (n--) {
		cin >> s;
		cnt += s == "LIE";
	}
	if (cnt % 2 == 1)
		cout << "LIE\n";
	else
		cout << "TRUTH\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
