#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define ii pair<int, int>
#define fi first
#define se second
int div2(int x)
{
	if (x < 0 && x % 2)
		x--;
	return x / 2;
}

void solve()
{
	int n;
	cin >> n;
	vector<ii> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].fi >> a[i].se;
	}
	if (n == 2) {
		cout << 1 << '\n';
		cout << 1 << '\n';
		return;
	}
	vector<vector<int> > groups(4);
	int cnt = 0;
	while (true) {
		for (int i = 0; i < n; i++) {
			int x = a[i].fi % 2;
			int y = a[i].se % 2;
			if (x == 0 && y == 0)
				groups[0].push_back(i);
			else if (x == 0)
				groups[1].push_back(i);
			else if (y == 0)
				groups[2].push_back(i);
			else
				groups[3].push_back(i);
		}
		cnt = 0;
		for (int i = 0; i < 4; i++)
			cnt += !groups[i].empty();
		if (cnt >= 2)
			break;
		for (int i = 0; i < n; i++) {
			a[i].fi = div2(a[i].fi);
			a[i].se = div2(a[i].se);
		}
		groups = vector<vector<int> >(4);
	}
	vector<int> A;
	if (cnt == 2) {
		for (int i = 0; i < 4; i++) {
			if (groups[i].empty())
				continue;
			if (A.empty()) {
				A = groups[i];
				break;
			}
		}
	} else {
		for (auto id : groups[0])
			A.push_back(id);
		for (auto id : groups[3])
			A.push_back(id);
	}
	cout << A.size() << '\n';
	for (auto i : A)
		cout << i + 1 << ' ';
	cout << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
