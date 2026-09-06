#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> b(n);
	for (int i = 0; i < n; i++)
		cin >> b[i];
	bool ok = true;
	for (int i = 0; i < n; i++) {
		if (b[i] != -1) {
			ok = false;
			break;
		}
	}
	if (ok) {
		cout << 1;
		for (int i = 1; i < n; i++)
			cout << 0;
		cout << "\n";
		return;
	}

	vector<int> d(n + 1, 0);
	for (int i = 0; i < n; i++) {
		if (b[i] <= 0)
			continue;
		int l = max(0ll, i - b[i] + 1);
		int r = min(n - 1, i + b[i] - 1);
		if (l <= r) {
			d[l]++;
			d[r + 1]--;
		}
	}
	vector<bool> sus(n, false);
	int cur = 0;
	for (int i = 0; i < n; i++) {
		cur += d[i];
		sus[i] = (cur > 0);
	}

	vector<int> res(n);
	for (int i = 0; i < n; i++) {
		if (b[i] == -1)
			continue;
		if (b[i] == 0) {
			if (sus[i]) {
				cout << -1 << "\n";
				return;
			}
			res[i] = 1;
			continue;
		}
		ok = false;
		int l = i - b[i];
		int r = i + b[i];
		if (l >= 0 && l < n && !sus[l]) {
			res[l] = 1;
			ok = true;
		}
		if (r >= 0 && r < n && !sus[r]) {
			res[r] = 1;
			ok = true;
		}
		if (!ok) {
			cout << -1 << "\n";
			return;
		}
	}
	for (auto x : res)
		cout << x;
	cout << "\n";
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
