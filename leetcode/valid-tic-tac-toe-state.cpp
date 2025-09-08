#include <array>
#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

int encode(char c)
{
	if (c == 'X')
		return 0;
	if (c == 'O')
		return 1;
	return 2;
}

array<int, 2> count_win(vector<string> &board)
{
	array<int, 2> count = { 0, 0 };

	for (int i = 0; i < 3; i++) {
		if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
			count[encode(board[i][0])]++;
		}
		if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
			count[encode(board[0][i])]++;
		}
	}

	if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
		count[encode(board[0][0])]++;

	if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
		count[encode(board[0][2])]++;

	return count;
}

bool validTicTacToe(vector<string> &board)
{
	array<int, 2> count = { 0, 0 };
	for (auto i = 0; i < 3; i++) {
		for (auto j = 0; j < 3; j++) {
			if (board[i][j] == ' ')
				continue;
			count[encode(board[i][j])]++;
		}
	}
	if (count[0] != count[1] || count[0] != count[1] + 1)
		return false;

	auto win = count_win(board);
	if (win[0] > 0 && win[1] > 0)
		return false;

	if (win[0] > 0 && count[1] == count[0])
		return false;
	if (win[1] > 0 && count[0] == count[1] + 1)
		return false;

	return true;
}

void solve()
{
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
