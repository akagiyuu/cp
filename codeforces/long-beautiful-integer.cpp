#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

bool is_ok(const vector<short> &x, const deque<short> &y)
{
	int n = x.size();
	int k = y.size();
	for (int i = 0; i < n; i++) {
		if (x[i] == y[i % k])
			continue;
		return x[i] <= y[i % k];
	}

	return true;
}

void solve()
{
	int n, k;
	cin >> n >> k;

	string s;
	cin >> s;
	vector<short> x(n);
	for (int i = 0; i < n; i++) {
		x[i] = s[i] - '0';
	}

	int m = n;
	deque<short> y(k);
	for (int i = 0; i < k; i++) {
		y[i] = x[i];
	}
	if (!is_ok(x, y)) {
		y[k - 1] = (y[k - 1] + 1) % 10;
		int carry = y[k - 1] == 0;
		int i = k - 2;
		while (i >= 0 && carry > 0) {
			y[i] = (y[i] + carry) % 10;
			carry = y[i] == 0;
			i--;
		}
		if (carry > 1) {
			y.push_front(carry);
			y.pop_back();
		}
	}

	cout << m << "\n";
	for (auto i = 0; i < m; i++) {
		cout << y[i % k];
	}
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
