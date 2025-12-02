#include <bits/stdc++.h>

#define int long long

using namespace std;
const int N = 2e7;

bool is_composite[N];
vector<int> primes;

void build()
{
	for (int i = 2; i < N; i++) {
		if (is_composite[i])
			continue;
		primes.push_back(i);
		for (int j = i * i; j < N; j += i) {
			is_composite[j] = true;
		}
	}
}

int calc_pow(int x, int p)
{
	int res = 0;
	while (x) {
		x /= p;
		res += x;
	}
	return res;
}

int solve(int n, int m)
{
	vector<int> max_pw(N, 0);
	for (int i = 0; i < (int)primes.size(); i++) {
		int pw = 1;
		int cur = primes[i];
		while (m >= cur) {
			pw++;
			cur *= primes[i];
		}
		pw--;
		max_pw[primes[i]] = pw;
	}
	int max_p = n;
	while (is_composite[max_p])
		max_p--;

	vector<int> ps;
	for (auto p : primes) {
		int cnt = 0;
		for (int i = max_p; i <= n; i++) {
			cnt += i % p;
		}
		if (cnt > 0)
			ps.push_back(p);
	}

	int res = 0;
	for (int x = max_p; x <= n - 1; x++) {
		int cur = LONG_LONG_MAX;
		for (auto p : ps) {
			if (max_pw[p] == 0)
				break;
			int v = calc_pow(x, p);
			if (v == 0) {
				cur = 0;
				break;
			}
			int vn = calc_pow(n, p);
			int pw = max_pw[p];
			for (; pw >= 1; pw--) {
				if ((v / pw) != (vn / pw)) {
					break;
				}
			}
			if (pw == 0)
				continue;
			v /= pw;
			if (v >= cur)
				break;
			cur = min(cur, v);
		}
		res += cur;
	}
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		cout << solve(n, m) << "\n";
	}
}
