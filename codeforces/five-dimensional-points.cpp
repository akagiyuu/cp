#include <bits/stdc++.h>

using namespace std;

#define int long long

int dot(const vector<int> &a, const vector<int> &b)
{
	int res = 0;
	for (int i = 0; i < 5; i++)
		res += a[i] * b[i];
	return res;
}
vector<int> sub(const vector<int> &a, const vector<int> &b)
{
	vector<int> res(5, 0);
	for (int i = 0; i < 5; i++)
		res[i] = a[i] - b[i];
	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<vector<int> > a(n, vector<int>(5, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 5; j++)
			cin >> a[i][j];
	}
	if (n > 11) {
		cout << 0 << '\n';
		return;
	}
	vector<int> res;
	for (int i = 0; i < n; i++) {
		bool ok = true;
		for (int j = 0; j < n; j++) {
			if (j == i)
				continue;
			for (int k = 0; k < n; k++) {
				if (k == i || k == j)
					continue;
				if (dot(sub(a[j], a[i]), sub(a[k], a[i])) > 0) {
					ok = false;
					break;
				}
			}
			if (!ok)
				break;
		}
		if (ok)
			res.push_back(i);
	}
	cout << res.size() << '\n';
	for (auto x : res)
		cout << x + 1 << ' ';
	cout << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
