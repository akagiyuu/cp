#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 1e6 + 7;

bool is_composite[N];

void build()
{
	is_composite[0] = is_composite[1] = true;
	for (int i = 0; i < N; i++) {
		if (is_composite[i])
			continue;
		for (int j = 2 * i; j < N; j += i) {
			is_composite[j] = true;
		}
	}
}

void solve()
{
	int n, e;
	cin >> n >> e;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int cnt = 0;
	auto cal = [](int l, int mid, int r) {
		return l * (r + 1) + r;
	};
	for (int i = 0; i < e; i++) {
		int j = n - 1 - i;

		int r = 0;
		int mid = -1;
		int l = 0;
		for (; j >= 0; j -= e) {
			if (a[j] == 1) {
				if (mid != -1)
					l++;
				else
					r++;
			} else if (!is_composite[a[j]]) {
				if (mid != -1) {
					cnt += cal(l, mid, r);
					r = l;
					l = 0;
				}

				mid = j;
			} else {
				if (mid != -1) {
					cnt += cal(l, mid, r);
				}
				mid = -1;
				r = 0;
				l = 0;
			}
		}
		if (mid != -1) {
			cnt += cal(l, mid, r);
		}
	}
	cout << cnt << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--)
		solve();
}
