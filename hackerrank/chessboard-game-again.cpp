#include <bits/stdc++.h>

#define int long long

using namespace std;
const int N = 16;
int g[N][N];

int grundy(int i, int j)
{
	if (g[i][j] != -1)
		return g[i][j];
	unordered_set<int> s;
	if (i - 2 >= 1 && j + 1 <= 15) {
		s.insert(grundy(i - 2, j + 1));
	}
	if (i - 2 >= 1 && j - 1 >= 1) {
		s.insert(grundy(i - 2, j - 1));
	}
	if (i + 1 <= 15 && j - 2 >= 1) {
		s.insert(grundy(i + 1, j - 2));
	}
	if (i - 1 >= 1 && j - 2 >= 1) {
		s.insert(grundy(i - 1, j - 2));
	}
	int mex = 0;
	while (s.find(mex) != s.end())
		mex++;
	g[i][j] = mex;
	return mex;
}

bool solve()
{
	int n;
	cin >> n;
	int res = 0, i, j;
	while (n--) {
		cin >> i >> j;
		res ^= grundy(i, j);
	}
	return res != 0;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			g[i][j] = -1;
		}
	}

	int t;
	cin >> t;
	while (t--) {
		if (solve())
			cout << "First\n";
		else
			cout << "Second\n";
	}
}
