#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 1001;

int cnt[N];

void solve()
{
	int n;
	cin >> n;
	for (int i = 0; i < n * n; i++) {
		int x;
		cin >> x;
		cnt[x]++;
	}
	int k = 1;
	int missing = n * n;
	vector<vector<int> > res(n, vector<int>(n, 0));
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < n / 2; j++) {
			while (k < N && cnt[k] < 4) {
				k++;
			}
			if (k == N)
				goto outer;
			res[i][j] = res[n - 1 - i][j] = res[i][n - 1 - j] = res[n - 1 - i][n - 1 - j] = k;
			missing -= 4;
			cnt[k] -= 4;
		}
	}
outer:
	if (n % 2 == 1) {
		k = 1;
		int half = n / 2;
		k = 1;
		for (int i = 0; i < half; i++) {
			while (k < N && cnt[k] < 2) {
				k++;
			}
			if (k == N)
				break;
			res[i][half] = res[n - 1 - i][half] = k;
			missing -= 2;
			cnt[k] -= 2;
		}

		for (int j = 0; j < half; j++) {
			while (k < N && cnt[k] < 2) {
				k++;
			}
			if (k == N)
				break;
			res[half][j] = res[half][n - 1 - j] = k;
			missing -= 2;
			cnt[k] -= 2;
		}

		k = 1;
		while (cnt[k] == 0)
			k++;
		res[half][half] = k;
		missing--;
	}
	if (missing > 0) {
		cout << "NO\n";
		return;
	}

	cout << "YES\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << res[i][j] << " ";
		}
		cout << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
