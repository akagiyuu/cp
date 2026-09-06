#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	string s;
	cin >> s;

	vector<int> cnt;
	int cur = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] == 0)
			cur++;
		else
			cnt.push_back(cur);
	}
	// for (auto x : cnt)
	// 	cout << x << " ";
	// cout << "\n";
	int m = cnt.size();
	if(m == 0) {
		for(int i = 0; i <= n; i++) cout << 0 << " ";
		cout << "\n";
		return;
	}
	vector<int> p(m);
	p[0] = cnt[0];
	for (int i = 1; i < m; i++) {
		p[i] = p[i - 1] + cnt[i];
	}
	auto cal = [&p](int l, int r) {
		if (l > 0)
			return p[r] - p[l - 1];
		return p[r];
	};
	cout << cal(0, m - 1) << " ";

	int cnt0 = 0, cnt1 = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '0')
			cnt0++;
		else
			cnt1++;
		int r = m - cnt1 - 1;
		int l = lower_bound(cnt.begin(), cnt.begin() + r + 1, cnt0) - cnt.begin();
		if (l > r) {
			cout << 0 << " ";
			continue;
		}
		int res = cal(l, r);
		res -= (r - l + 1) * cnt0;
		cout << res << " ";
	}
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
