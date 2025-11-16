#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	string s;
	cin >> s;
	int prev = s[0];
	int cnt = 1;
	vector<int> g;
	for (int i = 1; i < n; i++) {
		if (s[i] == prev) {
			cnt++;
			continue;
		}
		g.push_back(cnt);
		prev = s[i];
		cnt = 1;
	}
	g.push_back(cnt);
	n = g.size();
	for (int i = 0; i < n; i++) {
		cout << g[i] << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
