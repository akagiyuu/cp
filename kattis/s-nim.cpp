#include <bits/stdc++.h>

using namespace std;

#define int long long
const int N = 1e5 + 1;

void solve()
{
	int k;
	cin >> k;
	vector<int> s(k);
	for (int i = 0; i < k; i++) {
		cin >> s[i];
	}
	sort(s.begin(), s.end());

	int g[N];
	g[0] = 0;
	unordered_set<int> mex;
	for (int i = 1; i < N; i++) {
		mex.clear();
		for (auto move : s) {
			if (move > i)
				break;
			mex.insert(g[i - move]);
		}
		int cur = 0;
		while (mex.find(cur) != mex.end())
			cur++;
		g[i] = cur;
	}
	int m;
	cin >> m;
	while (m--) {
		int l, x, res = 0;
		cin >> l;
		for (int i = 0; i < l; i++) {
			cin >> x;
			res ^= g[x];
		}
		if (res == 0)
			cout << "L";
		else
			cout << "W";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
