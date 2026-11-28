#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e7 + 7;

int cnt[N];

void build()
{
	vector<int> lp(N, 0);
	vector<int> pr;

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

	for (int i = 2; i < N; i++) {
		if (lp[i] == i) {
			cnt[i] = 1;
			continue;
		}
		int j = i / lp[i];
		if (lp[j] == lp[i])
			cnt[i] = cnt[j];
		else
			cnt[i] = cnt[j] + 1;
	}
}
int binpow(int x, int e)
{
	int r = 1;
	while (e) {
		if (e & 1)
			r = r * x;
		x = x * x;
		e >>= 1;
	}
	return r;
}

void solve()
{
	int c, d, x;
	cin >> c >> d >> x;
	int res = 0;

	auto calc = [&](int g) {
		int s = (x / g) + d;
		if (s % c != 0)
			return;
		s /= c;
		res += binpow(2, cnt[s]);
	};
	for (int i = 1; i * i <= x; i++) {
		if (x % i != 0)
			continue;
		calc(i);
		int j = x / i;
		if (j != i)
			calc(j);
	}
	cout << res << '\n';
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
