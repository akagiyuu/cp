#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e7;

ll lp[N];

void build()
{
	vector<ll> pr;
	for (ll i = 2; i < N; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (ll j = 0; i * pr[j] < N; j++) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i])
				break;
		}
	}
}

ll find_k(ll x, ll d)
{
	return (d - x % d) % d;
}

ll solve()
{
	ll x, y;
	cin >> x >> y;
	if (x > y)
		swap(x, y);
	ll diff = y - x;
	if (diff == 1)
		return -1;

	ll kmin = LONG_LONG_MAX;
	while (diff > 1) {
		ll p = lp[diff];
		kmin = min(kmin, find_k(x, p));
		diff /= p;
	}
	kmin--;
	ll res = max(kmin + 1, 0ll);
	return res;
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
		cout << solve() << "\n";
}
