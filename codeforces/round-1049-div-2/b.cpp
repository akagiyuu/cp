#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

const ll N = 1e7;
ll sieve[N + 1];

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

void solve()
{
	ll x;
	cin >> x;
	ll count = floor(log10((double)x)) + 1;
	if (count % 2 == 1) {
		cout << 10 * x << "\n";
		return;
	}

	ll y = 8 * x;
	ll count2 = floor(log10((double)y)) + 1;
	if ((x * (ll)pow(10, count2) + y) % (x + y) == 0) {
		cout << y << "\n";
	} else {
		cout << "\n";
	}
}

int main()
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
