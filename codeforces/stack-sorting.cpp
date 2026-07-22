#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> a(k);
	vector<bool> exist(n, false);
	for (int i = 0; i < k; i++) {
		cin >> a[i];
		a[i]--;
		exist[a[i]] = true;
	}
	stack<int> s;
	s.push(n);
	int require = 0;
	for (int i = 0; i < k; i++) {
		s.push(a[i]);
		while (!s.empty() && s.top() == require) {
			s.pop();
			require++;
		}
	}
	while (!s.empty()) {
		for (int i = s.top() - 1; i >= require; i--) {
			if (exist[i]) {
				cout << -1 << "\n";
				return;
			}
			a.push_back(i);
		}
		require = s.top() + 1;
		s.pop();
	}
	for (auto x : a)
		cout << x + 1 << " ";
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
