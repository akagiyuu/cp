#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

bool solve()
{
	int n, m;
	string s;
	cin >> n >> m >> s;
	if (m >= 50)
		return true;
	if (m >= (n + 4) / 5)
		return true;
	int mins = (s[0] - '0') * 600 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + s[4] - '0';
	return mins >= 240;
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
