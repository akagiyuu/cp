#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const int N = 18;
const int M = 65;
int pr[N] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
};
vector<int> add, sub;

void build()
{
	for (int mask = 1; mask < (1ll << N); mask++) {
		int r = 1;
		bool ok = true;
		for (int j = 0; j < N; j++) {
			if ((mask >> j) & 1)
				r *= pr[j];
			if (r >= M) {
				ok = false;
				break;
			}
		}
		if (!ok)
			continue;
		if (__builtin_parity(mask) == 1)
			sub.push_back(r);
		else
			add.push_back(r);
	}
	sort(add.begin(), add.end());
	sort(sub.begin(), sub.end());
}

__int128 binpow(__int128 x, __int128 e)
{
	__int128 r = 1;
	while (e) {
		if (e & 1)
			r = r * x;
		x = x * x;
		e >>= 1;
	}
	return r;
}

int iroot(__int128 n, __int128 r)
{
	__int128 res = floorl(powl((double)n, 1. / (double)r));
	while (binpow(res + 1, r) <= n)
		res++;
	while (binpow(res, r) > n)
		res--;
	return res;
}

void solve()
{
	int n;
	cin >> n;
	int res = n - 1;
	for (int i = 0; i < (int)add.size(); i++) {
		int left = 2;
		int right = iroot(n, add[i]);
		int cnt = max(right - left + 1, 0ll);
		res += cnt;
		if (cnt == 0)
			break;
	}
	for (int i = 0; i < (int)sub.size(); i++) {
		int left = 2;
		int right = iroot(n, sub[i]);
		int cnt = max(right - left + 1, 0ll);
		res -= cnt;
		if (cnt == 0)
			break;
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
