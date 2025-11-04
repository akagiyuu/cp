#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

#define int long long

using namespace std;

const int N = 101;
int g[N][N];

void build()
{
	set<int> s;
	for (int i = 0; i < N; i++) {
		g[0][i] = -1;
		g[i][0] = -1;
		g[i][i] = -1;
	}
	for (int dist = 1; dist < N; dist++) {
		for (int i = dist, j = 0; j < dist; j++) {
			if (g[i][j] == -1)
				continue;
			s.clear();
			for (int u = 1; u <= i; u++) {
				s.insert(g[i - u][j]);
			}
			for (int u = 1; u <= j; u++) {
				s.insert(g[i][j - u]);
			}
			for (int u = 1; u <= min(i, j); u++) {
				s.insert(g[i - u][j - u]);
			}
			int mex = 0;
			while (s.find(mex) != s.end())
				mex++;
			g[i][j] = mex;
		}
		for (int j = dist, i = 0; i < dist; i++) {
			s.clear();
			if (g[i][j] == -1)
				continue;
			for (int u = 1; u <= i; u++) {
				s.insert(g[i - u][j]);
			}
			for (int u = 1; u <= j; u++) {
				s.insert(g[i][j - u]);
			}
			for (int u = 1; u <= min(i, j); u++) {
				s.insert(g[i - u][j - u]);
			}
			int mex = 0;
			while (s.find(mex) != s.end())
				mex++;
			g[i][j] = mex;
		}

		int i = dist, j = dist;
		s.clear();
		if (g[i][j] == -1)
			continue;
		for (int u = 1; u <= i; u++) {
			s.insert(g[i - u][j]);
		}
		for (int u = 1; u <= j; u++) {
			s.insert(g[i][j - u]);
		}
		for (int u = 1; u <= min(i, j); u++) {
			s.insert(g[i - u][j - u]);
		}
		int mex = 0;
		while (s.find(mex) != s.end())
			mex++;
		g[i][j] = mex;
	}
	// for (int i = 0; i < 3; i++) {
	// 	for (int j = 0; j < 3; j++) {
	// 		cout << g[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }
}

void solve()
{
	int n, row, col, res = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> row >> col;
		res ^= g[row][col];
	}
	if (res == 0)
		cout << "N\n";
	else
		cout << "Y\n";
}

signed main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
