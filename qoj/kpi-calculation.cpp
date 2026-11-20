#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve()
{
	string s;
	int res = 0;
	while (getline(cin, s)) {
		if (s.empty())
			continue;
		int cur = 0;
		for (auto c : s) {
			if (c != ' ')
				break;
			cur++;
		}
		res += cur;
	}
	cout << res << '\n';
}

signed main()
{
	solve();
}
