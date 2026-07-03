#include <bits/stdc++.h>
#include <queue>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 2;
const int INF = 1e9;

struct Data {
	int i;
	int j;
	int water;
	Data(int i, int j, int water)
	{
		this->i = i;
		this->j = j;
		this->water = water;
	}
};

bool solve()
{
	int m, k;
	cin >> m >> k;
	array<string, N> a;
	cin >> a[0] >> a[1];
	a[0].push_back('-');
	a[1].push_back('-');
	m++;

	queue<Data> q;
	array<vector<bool>, 2> visisted = { vector<bool>(m, false), vector<bool>(m, false) };
	q.push(Data(0, 0, 0));
	while (!q.empty()) {
		auto [i, j, water] = q.front();
		q.pop();
		if (visisted[i][j])
			continue;
		visisted[i][j] = true;
		if (j == m - 1)
			return true;
		if (j > 0 && a[i][j - 1] == '-' && j - 1 > water) {
			q.push(Data(i, j - 1, water + 1));
		}
		if (j < m - 1 && a[i][j + 1] == '-' && j + 1 > water) {
			q.push(Data(i, j + 1, water + 1));
		}
		int ni = (i + 1) % 2;
		int nj = min(j + k, m - 1);
		if (a[ni][nj] == '-' && nj > water) {
			q.push(Data(ni, nj, water + 1));
		}
	}

	return false;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	if (solve())
		cout << "YES\n";
	else
		cout << "NO\n";
}
