#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

ll solve()
{
	int n;
	cin >> n;
	vector<ll> sieve(n + 1, 0);
	ll count = 0;
	for (int i = 2; i <= n; i++) {
		if (sieve[i] == 0) {
			for (int j = 2 * i; j <= n; j += i) {
				sieve[j]++;
			}
			continue;
		}
		if (sieve[i] == 2) {
			count++;
		}
	}
	return count;
}

int main()
{
	cout << solve();
}
