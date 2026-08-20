#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

int cal(const vector<int> &a)
{
	int res = 0;
	int p = 1;
	for (auto x : a) {
		res += x * p;
		p *= 2;
	}
	return res;
}

void solve()
{
	int k;
	cin >> k;
	string s;
	cin >> s;
	int n = s.size();
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		a[i] = s[n - 1 - i] - '0';
	}
	int cnt = 0;
	if (cal(a) <= k) {
		cout << cnt << "\n";
		return;
	}
	for (int i = n - 2; i >= 0; i--) {
		if (a[i] != 1)
			continue;
		a.erase(a.begin() + i);
		cnt++;
		if (cal(a) <= k)
			break;
	}
	int cur = cal(a);
	while (cur > k) {
		cur /= 2;
		cnt++;
	}
	cout << cnt << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
