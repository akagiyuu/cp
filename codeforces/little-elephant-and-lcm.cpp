#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

int add(int a, int b)
{
	a += b;
	return a < MOD ? a : a - MOD;
}
int sub(int a, int b)
{
	a -= b;
	return a < 0 ? a + MOD : a;
}
int powmod(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	int m = *max_element(a.begin(), a.end());
	int res = 0;
	for (int l = 1; l <= m; l++) {
		// cout << l << "\n";
		vector<int> divisors;
		for (int i = 1; i * i <= l; i++) {
			if(l % i != 0) continue;
			int j = l / i;
			divisors.push_back(i);
			if (i != j)
				divisors.push_back(j);
		}
		sort(divisors.begin(), divisors.end());
		int sz = divisors.size();
		vector<int> cnt(sz);
		for (int i = 0; i < sz; i++) {
			cnt[i] = lower_bound(a.begin(), a.end(), divisors[i]) - a.begin();
			// cout << divisors[i] << " " << cnt[i] << "\n";
		}
		int cur = 1;
		// cout << "\n";
		for (int i = 0; i < sz - 1; i++) {
			int segment_sz = cnt[i + 1] - cnt[i];
			cur = (cur * powmod(i + 1, segment_sz)) % MOD;
		}
		int segment_sz = n - cnt[sz - 1];
		cur = (cur * sub(powmod(sz, segment_sz), powmod(sz - 1, segment_sz))) % MOD;
		// cout << n - cnt[sz - 1] << "\n";
		res = add(res, cur);
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
