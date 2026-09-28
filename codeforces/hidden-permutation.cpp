#include <bits/stdc++.h>

using namespace std;

#define int long long

void next_permutation_cyc(vector<int> &a)
{
	int n = a.size();
	if (!next_permutation(a.begin(), a.end())) {
		for (int i = 0; i < n; i++) {
			a[i] = i + 1;
		}
	}
}
bool equal(const vector<int> &a, const vector<int> &b)
{
	int n = a.size();
	for (int i = 0; i < n; i++) {
		if (a[i] == b[i])
			continue;
		return false;
	}
	return true;
}

void solve()
{
	string type;
	cin >> type;
	int n;
	cin >> n;
	if (type == "first") {
		vector<int> a(n);
		for (int i = 0; i < n; i++)
			cin >> a[i];
		vector<vector<int> > b(n);
		for (int i = 0; i < n; i++) {
			b[i] = a;
			next_permutation_cyc(a);
		}
		for (int i = 0; i < n; i++) {
			for (auto x : b[i])
				cout << x << ' ';
			cout << '\n';
		}
	} else {
		vector<vector<int> > b(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cin >> b[i][j];
		}
		sort(b.begin(), b.end(), [n](const vector<int> &a, const vector<int> &b) {
			for (int i = 0; i < n; i++) {
				if (a[i] == b[i])
					continue;
				return a[i] < b[i];
			}
			return false;
		});
		int k = 0;
		for (int i = 0; i < n - 1; i++) {
			auto tmp = b[i];
			next_permutation_cyc(tmp);
			if (equal(tmp, b[i + 1]))
				continue;
			k = i + 1;
			break;
		}
		for (auto x : b[k])
			cout << x << ' ';
		cout << '\n';
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
