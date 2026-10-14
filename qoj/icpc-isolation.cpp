#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int N = 27;

string teams[N] = {
	"UW",  "UJ",  "UWR", "MAP", "PW",  "AGH", "PG", "NLU", "PUT", "PO", "PWR", "SGGW", "UMCS", "UR",
	"ZUT", "DTP", "GOO", "HUA", "KUL", "PL",  "PM", "PS",  "UAM", "UG", "UMK", "UO",   "WAT",
};
int cnt[N] = { 11, 9, 8, 7, 6, 5, 4, 3, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

bool check(int i, int j, const vector<vector<int> > &grid)
{
	if (i > 0 && grid[i - 1][j] == grid[i][j])
		return false;
	if (j > 0 && grid[i][j - 1] == grid[i][j])
		return false;
	if (i > 0 && j > 0 && grid[i - 1][j - 1] == grid[i][j])
		return false;
	if (i > 0 && j + 1 < 10 && grid[i - 1][j + 1] == grid[i][j])
		return false;
	return true;
}

bool backtrack(int k, vector<vector<int> > &grid)
{
	if (k == 80)
		return true;
	int i = k / 10;
	int j = k % 10;
	for (int x = 0; x < N; x++) {
		if (cnt[x] == 0)
			continue;
		grid[i][j] = x;
		cnt[x]--;
		if (check(i, j, grid) && backtrack(k + 1, grid))
			return true;
		cnt[x]++;
		grid[i][j] = -1;
	}
	return false;
}

void solve()
{
	string f;
	cin >> f;
	int i = find(teams, teams + N, f) - teams;
	cnt[i]--;
	vector<vector<int> > grid(8, vector<int>(10, -1));
	grid[0][0] = i;
	assert(backtrack(1, grid));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			cout << teams[grid[i][j]] << ' ';
		}
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
