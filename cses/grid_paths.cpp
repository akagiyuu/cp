#include <bits/stdc++.h>
#include <ios>
#include <string>

using namespace std;

typedef long long ll;

int dirs[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
string s;

ll solve(int i, int x, int y, vector<vector<bool> > is_visited)
{
	while (i < s.length() && s[i] != '?') {
		switch (s[i]) {
		case 'R': {
			x++;
			break;
		}
		case 'L': {
			x--;
			break;
		}
		case 'D': {
			y++;
			break;
		}
		case 'U': {
			y--;
			break;
		}
		}
		if (x < 0 || x >= 7 || y < 0 || y >= 7 || is_visited[x][y]) {
			return 0;
		}
		is_visited[x][y] = true;
		i++;
	}

	if (i == s.length()) {
		return 1;
	}

	ll count = 0;
	for (auto dir : dirs) {
		int next_x = x + dir[0];
		int next_y = y + dir[1];
		if (next_x < 0 || next_x >= 7 || next_y < 0 || next_y >= 7 || is_visited[next_x][next_y]) {
			continue;
		}
		is_visited[next_x][next_y] = true;
		count += solve(i + 1, next_x, next_y, is_visited);
		is_visited[next_x][next_y] = false;
	}
	return count;
}

int main()
{
	ios_base::sync_with_stdio();
	cin.tie(NULL);
	cout.tie(NULL);
	vector<vector<bool> > is_visited(7, vector<bool>(7, false));
	is_visited[0][0] = true;
	cin >> s;
	cout << solve(0, 0, 0, is_visited);
}
