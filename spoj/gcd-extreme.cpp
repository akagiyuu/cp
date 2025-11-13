#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve(const vector<int> &input, int max_n)
{
	vector<int> phi(max_n + 1, 0);
	vector<int> primes;
	primes.reserve(max_n / 10);
	vector<char> is_comp(max_n + 1, 0);
    phi[1] = 1;
	for (int i = 2; i <= max_n; ++i) {
		if (!is_comp[i]) {
			primes.push_back(i);
			phi[i] = i - 1;
		}
		for (int p : primes) {
			long long v = p * i;
			if (v > max_n)
				break;
			is_comp[v] = 1;
			if (i % p == 0) {
				phi[v] = phi[i] * p;
				break;
			} else {
				phi[v] = phi[i] * (p - 1);
			}
		}
	}
	for (int i = 1; i <= max_n; i++) {
		phi[i] += phi[i - 1];
	}

	for (auto n : input) {
		int res = -n * (n + 1) / 2;
		int l = 1;
		while (l <= n) {
			int x = n / l;
			int r = n / x;
			res += x * x * (phi[r] - phi[l - 1]);
			l = r + 1;
		}
		cout << res / 2 << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<int> input;
	int max_n = 0;

	int n;
	cin >> n;
	while (n != 0) {
		input.push_back(n);
		max_n = max(max_n, n);
		cin >> n;
	}
	solve(input, max_n);
}
