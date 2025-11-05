#include <bits/stdc++.h>

#define int long long

using namespace std;

pair<bool, vector<array<int, 3> > > solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int sum = 0;
	for (auto x : a)
		sum += x;
	if (sum % n != 0) {
		return { false, {} };
	}

	int required = sum / n;

	vector<array<int, 3> > moves;
	for (int i = 1; i < n; i++) {
		int x = (a[i] - 1) / (i + 1);
		moves.push_back({ i, 0, x });
		a[0] += x * (i + 1);
		a[i] -= x * (i + 1);
	}
	for (int i = 1; i < n; i++) {
		if (required >= a[i])
			continue;
		int x = a[i] - required;
		moves.push_back({ 0, i, (x + i) / (i + 1) });
		moves.push_back({ i, 0, 1 });
	}
	for (int i = 1; i < n; i++) {
		int x = required - a[i];
		if (x < 0)
			continue;
		moves.push_back({ 0, i, x });
	}
	return { true, moves };
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		auto [possible, moves] = solve();
		if (!possible) {
			cout << "-1\n\n";
			continue;
		}

		cout << moves.size() << "\n";
		for (auto move : moves) {
			cout << move[0] + 1 << " " << move[1] + 1 << " " << move[2] << "\n";
		}
		cout << "\n";
	}
}
