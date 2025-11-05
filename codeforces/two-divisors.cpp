#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e7 + 1;

int lp[N];
vector<int> pr;

void build()
{
	for (int i = 2; i < N; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; i * pr[j] < N; j++) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i])
				break;
		}
	}
}

void solve()
{
	int n;
	cin >> n;

	vector<array<int, 2> > res(n, { -1, 1 });
	int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		int j = 0;
		while (x > 1) {
			int cur = lp[x];
			if (j == 0)
				res[i][j++] = cur;
			else
				res[i][j] *= cur;
			while (x % cur == 0)
				x /= cur;
		}
		if (res[i][j] == 1)
			res[i] = { -1, -1 };
	}
	for (int i = 0; i < n; i++) {
		cout << res[i][0] << " ";
	}
	cout << "\n";
	for (int i = 0; i < n; i++) {
		cout << res[i][1] << " ";
	}
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
