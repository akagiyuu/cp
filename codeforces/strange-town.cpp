#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>

#define int long long

using namespace std;

bool check(const vector<vector<int> > &mat)
{
	int n = mat.size();
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		v[i] = i;
	}
	int sum = -1;
	do {
		int cur = 0;
		for (int i = 0; i < n; i++) {
			int j = (i + 1) % n;
			cur += mat[i][j];
		}
		if (sum == -1) {
			sum = cur;
			continue;
		}
		if (cur != sum)
			return false;
	} while (next_permutation(v.begin(), v.end()));
	return true;
}

void print(const vector<vector<int> > &mat)
{
	int n = mat.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << mat[i][j] << " ";
		}
		cout << "\n";
	}
}

void generate(vector<vector<int> > &mat, int i, int j)
{
	int n = mat.size();
	if (i >= n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				mat[j][i] = mat[i][j];
			}
		}
		if (check(mat)) {
			print(mat);
			cout << "\n";
		}
		return;
	}
	int nexti = i;
	int nextj = j + 1;
	if (nextj == i) {
		nexti++;
		nextj = 0;
	}
	for (int x = 1; x <= 9; x++) {
		mat[i][j] = x;
		generate(mat, nexti, nextj);
	}
}

void generate(int n)
{
	vector<vector<int> > mat(n, vector<int>(n, 0));
	generate(mat, 1, 0);
}

void solve()
{
	int n;
	cin >> n;
	vector<vector<int> > a(n, vector<int>(n, 0));
	int cur = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			a[i][j] = cur;
			a[j][i] = cur;
			cur++;
		}
	}
	assert(check(a));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// // generate(5);
	// cout << check(a) << "\n";

	solve();
}
