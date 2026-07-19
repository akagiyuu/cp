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

	vector<int> ms(n);
	ms[n - 1] = a[n - 1];
	for (int i = n - 2; i >= 0; i--)
		ms[i] = min(ms[i + 1], a[i]);

	priority_queue<int, vector<int>, greater<int> > q;
	for (int i = 0; i < n; i++) {
		int m = ms[i];
		if (!q.empty()) {
			m = min(m, q.top());
		}
		if (a[i] > m) {
			q.push(a[i] + 1);
		} else {
			cout << a[i] << " ";
		}
	}
	while (!q.empty()) {
		cout << q.top() << " ";
		q.pop();
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
