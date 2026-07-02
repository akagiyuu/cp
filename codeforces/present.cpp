#include <bits/stdc++.h>

using namespace std;

#define int long long

bool check(int r, int m, int w, const vector<int> &a)
{
	int n = a.size();
	queue<int> q;

	for (int i = 0; i < n; i++) {
		while (!q.empty() && i >= (q.front() + w))
			q.pop();
		if ((a[i] + (int)q.size()) >= r)
			continue;
		while (m > 0 && (a[i] + (int)q.size()) < r) {
			q.push(i);
			m--;
		}
		if ((a[i] + (int)q.size()) < r)
			return false;
	}

	return true;
}

void solve()
{
	int n, m, w;
	cin >> n >> m >> w;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int l = 0;
	int r = 0;
	for (int i = 0; i < n; i++) {
		r = max(r, a[i]);
	}
	r += m;
	while (l < r) {
		int mid = (l + r + 1) / 2;
		if (check(mid, m, w, a)) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}
	cout << l << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
