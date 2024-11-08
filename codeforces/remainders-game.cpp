#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

const ll MOD = 1000000007;
const ll N = 1e7;
ll sieve[N + 1];
ll factors[N + 1];

void build()
{
	vector<ll> ps;
	for (ll i = 2; i <= N; i++) {
		if (sieve[i] == 0) {
			sieve[i] = i;
			ps.push_back(i);
		}
		for (auto p : ps) {
			ll next = p * i;
			if (next > N) {
				break;
			}
			sieve[next] = p;
			if (p == sieve[i]) {
				break;
			}
		}
	}
}

bool solve()
{
	ll n, k;
	cin >> n >> k;

	ll max_factor = 0;
	ll factor_count = 0;
	while (k > 1) {
		ll factor = sieve[k];
		ll count = 0;
		while (k % factor == 0) {
			count++;
			k /= factor;
		}
		factors[factor] = count;
		max_factor = max(factor, max_factor);
		factor_count++;
	}

	ll c;
	for (ll i = 0; i < n; i++) {
		cin >> c;
		while (c > 1) {
			ll factor = sieve[c];
			if (factor > max_factor) {
				break;
			}
			ll count = 0;
			while (c % factor == 0) {
				c /= factor;
				count++;
			}
			ll v = factors[factor];
			if (v == 0)
				continue;
			if (count >= v) {
				factors[factor] = 0;
				factor_count--;
				if (factor_count == 0)
					return true;
			}
		}
		if (factor_count == 0)
			return true;
	}

	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	build();
	cout << (solve() ? "Yes" : "No");
}
