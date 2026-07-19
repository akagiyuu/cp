#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 1e5 + 1;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int cnt = 0;
	multiset<int> s;
	for (auto x : a) {
		if (s.find(x) == s.end())
			cnt++;
		s.insert(x);
	}

	int res = 0;
	vector<bool> visited(N, false);
	for (auto x : a) {
		s.erase(s.find(x));
		if (s.find(x) == s.end()) {
			cnt--;
		}
		if (visited[x])
			continue;
		visited[x] = true;

		res += cnt;
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
