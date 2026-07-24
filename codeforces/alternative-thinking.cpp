#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

int solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;

	vector<int> comps;
	int cur = s[0];
	int cnt = 1;
	for (int i = 1; i < n; i++) {
		if (s[i] == cur) {
			cnt++;
		} else {
			comps.push_back(cnt);
			cur = s[i];
			cnt = 1;
		}
	}
	comps.push_back(cnt);

	cnt = 0;
	for (auto x : comps) {
		cnt += x >= 2;
		if (x >= 3)
			return comps.size() + 2;
	}
	if (cnt >= 2)
		return comps.size() + 2;
	if (cnt >= 1)
		return comps.size() + 1;

	return comps.size();
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
