#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> wall_ls(n), wall_rs(n);
	vector<vector<int> > doors;
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k >> wall_ls[i] >> wall_rs[i];
		doors.push_back(vector<int>(k));
		for (int j = 0; j < k; j++)
			cin >> doors[i][j];
	}

	vector<pi> lefts;
	vector<int> sums(n), rights(n);
	multiset<int> right_set;
	for (int i = 0; i < n; i++) {
		int s = wall_ls[i];
		for (auto d : doors[i]) {
			lefts.push_back({ i, s });
			s += d;
		}
		lefts.push_back({ i, s });
		sums[i] = s - wall_ls[i];
		rights[i] = wall_rs[i] - sums[i];
		right_set.insert(rights[i]);
		// cout << rights[i] << " ";
	}
	// cout << "\n";
	sort(lefts.begin(), lefts.end(), [](const pi &a, const pi &b) { return a.se < b.se; });
	// for (auto [i, l] : lefts) {
	// 	cout << "{ " << i << ", " << l << " }\n";
	// }

	vector<bool> contain(n, false);
	int missing = n;
	int k = 0;
	while (missing > 0) {
		auto [i, l] = lefts[k];
		right_set.erase(right_set.find(rights[i]));
		rights[i] = wall_rs[i] - sums[i] + l - wall_ls[i];
		right_set.insert(rights[i]);
		// cout << i << " " << l << rs.calc(0, n - 1) << "\n";

		if (!contain[i])
			missing--;
		contain[i] = true;
		k++;
	}

	int res = max(0ll, *right_set.begin() - lefts[k - 1].se);
	int m = lefts.size();
	for (; k < m; k++) {
		auto [i, l] = lefts[k];
		// cout << i << " " << l << rs.calc(0, n - 1) << "\n";
		right_set.erase(right_set.find(rights[i]));
		rights[i] = wall_rs[i] - sums[i] + l - wall_ls[i];
		right_set.insert(rights[i]);
		res = max(res, *right_set.begin() - l);
	}

	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
