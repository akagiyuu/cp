#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

ll phi(ll n)
{
	ll res = n;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i != 0)
			continue;

		while (n % i == 0) {
			n /= i;
		}
		res -= res / i;
	}
	if (n > 1)
		res -= res / n;
	return res;
}

void solve()
{
	ll n, k;
	cin >> n >> k;
	ll repeat_count = (k + 1) / 2;
	for (ll i = 0; i < repeat_count; i++) {
		ll next = phi(n);
        if(n == next)
            break;
        n = next;
	}
	n %= MOD;
	cout << n;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
