#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	string s;
	cin >> s;
	int n = s.size();
	int cnt6 = 0, cnt7 = 0;
	for (int i = 0; i < n; i++) {
		cnt7 += s[i] == '7';
	}
	for (int i = 0; i < n; i++) {
		if (s[i] == '6')
			cnt6++;
		if (s[i] == '7')
			cnt7--;
		if (s[i] == 'C') {
			if (cnt6 > cnt7)
				s[i] = '6';
			else
				s[i] = '7';
		}
	}
	for (int i = 0; i < n; i++) {
		cnt7 += s[i] == '7';
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '6') {
			cnt += cnt7;
			cnt6++;
		}
		if (s[i] == '7')
			cnt7--;
	}
	cout << cnt << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
