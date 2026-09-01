#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>

const int MOD = 1000000007;

bool is_prime(int n)
{
	if (n < 2)
		return false;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}

bool is_prime_pow(int x, int &p, int &k)
{
	if (x < 2)
		return false;
	for (int d = 2; d * d <= x; d++) {
		if (x % d != 0)
			continue;
		int tmp = x;
		k = 0;
		while (tmp % d == 0) {
			tmp /= d;
			k++;
		}
		if (tmp == 1) {
			p = d;
			return true;
		}
		return false;
	}

	p = x;
	k = 1;
	return true;
}

int get_pow(int n, int p)
{
	int cnt = 0;
	while (n > 0 && n % p == 0) {
		cnt++;
		n /= p;
	}
	return cnt;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	vector<int> valid;
	for (int x = 2; x <= 43; x++) {
		int p, k;
		if (!is_prime_pow(x, p, k))
			continue;

		vector<pi> reqs;
		for (int q = 2; q < x; q++) {
			if (!is_prime(q))
				continue;
			int pw = q;
			int max_e = 1;
			while (pw * q < x) {
				pw *= q;
				max_e++;
			}
			reqs.push_back({ q, max_e });
		}

		bool possible = false;
		int l = 0;
		while (l < n) {
			if (get_pow(a[l], p) >= k) {
				l++;
				continue;
			}
			int r = l;
			while (r < n && get_pow(a[r], p) < k)
				r++;

			int sz = reqs.size();
			vector<int> satisfied(sz, 0);
			int ok_cnt = 0;
			int ptr_r = l;
			for (int ptr_l = l; ptr_l < r; ++ptr_l) {
				while (ptr_r < r && ok_cnt < sz) {
					for (int i = 0; i < sz; ++i) {
						if (get_pow(a[ptr_r], reqs[i].first) >= reqs[i].second) {
							if (satisfied[i] == 0)
								ok_cnt++;
							satisfied[i]++;
						}
					}
					ptr_r++;
				}

				if (ok_cnt == sz) {
					possible = true;
					break;
				}

				for (int i = 0; i < sz; ++i) {
					if (get_pow(a[ptr_l], reqs[i].first) >= reqs[i].second) {
						satisfied[i]--;
						if (satisfied[i] == 0)
							ok_cnt--;
					}
				}
			}

			if (possible)
				break;
			l = r;
		}
		if (possible) {
			valid.push_back(x);
		}
	}

	cout << valid.size() << "\n";
	for(auto x: valid) cout << x << " ";
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
