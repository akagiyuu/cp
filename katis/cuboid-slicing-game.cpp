#include <bits/stdc++.h>

using namespace std;

#define int long long
const int N = 31;

int g[N][N][N];

int grundy(int i, int j, int k)
{
	if (i > j)
		swap(i, j);
	if (j > k)
		swap(j, k);
	if (i > j)
		swap(i, j);

	if (g[i][j][k] != -2)
		return g[i][j][k];

	set<int> s;
	for (int i1 = 0; i1 < i; i1++) {
		int subi[2] = { i1, i - 1 - i1 };

		for (int j1 = 0; j1 < j; j1++) {
			int subj[2] = { j1, j - 1 - j1 };

			for (int k1 = 0; k1 < k; k1++) {
				int subk[2] = { k1, k - 1 - k1 };

				int cur = 0;
				for (int mask = 0; mask < (1 << 3); mask++) {
					int ni = subi[mask & 1];
					int nj = subj[(mask >> 1) & 1];
					int nk = subk[(mask >> 2) & 1];

					cur ^= grundy(ni, nj, nk);
				}
				s.insert(cur);
			}
		}
	}
	int mex = 0;
	while (s.find(mex) != s.end())
		mex++;
	g[i][j][k] = mex;
	return mex;
}

void build()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				g[i][j][k] = -2;
			}
		}
	}
	g[0][0][0] = 0;
}

bool solve()
{
	int n, x, y, z, res = 0;
	cin >> n;

	while (n--) {
		cin >> x >> y >> z;
		res ^= grundy(x, y, z);
	}

	return res != 0;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	map<string, string> m;
	m["RUBEN"] = "ALBERT";
	m["ALBERT"] = "RUBEN";

	string cur;
	cin >> cur;
	build();

	if (solve())
		cout << cur;
	else
		cout << m[cur];
}
