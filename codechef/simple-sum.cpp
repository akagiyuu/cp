#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e7 + 1;

int f[N], cnt[N];
bool is_composite[N];

int binpow(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1)
			res *= a;
		a *= a;
		b >>= 1;
	}
	return res;
}

int f_pk(int p, int k)
{
	int res = 0;
	int cur = 1;
	for (int i = 0; i <= 2 * k; i++) {
		res += cur;
		cur *= -p;
	}
	return res;
}

void build()
{
	vector<int> pr;
	f[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!is_composite[i]) {
			pr.push_back(i);
			f[i] = 1;
			cnt[i] = 1;
		}
		for (int j = 0; j < (int)pr.size() && i * pr[j] < N; ++j) {
			is_composite[i * pr[j]] = true;
			if (i % pr[j] == 0) {
				// change this
				f[i * pr[j]] = f[i / binpow(pr[j], cnt[i])] * f_pk(i, cnt[i + 1]);
				cnt[i * pr[j]] = cnt[i] + 1;
				break;
			} else {
				f[i * f[j]] = f[i] * f[pr[j]];
				cnt[i * pr[j]] = 1;
			}
		}
	}
}

void solve()
{
	int n;
	cin >> n;
	cout << f[n] << "\n";
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
