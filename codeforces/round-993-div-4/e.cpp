#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll k, l1, r1, l2, r2;
	cin >> k >> l1 >> r1 >> l2 >> r2;

	ll l = ceil((log((double)l2) - log((double)r1)) / log((double)k));
	l = max(l, 0ll);

	ll k_pow = pow(k, l);
	while (k_pow * r1 >= l2) {
		k_pow /= k;
		l -= 1;
	}
	k_pow *= k;
	if (k_pow == 0) {
		k_pow = 1;
	}

	ll res = 0;

	for (; k_pow * l1 <= r2; k_pow *= k) {
		ll left = max(l1, (l2 - 1) / k_pow + 1);
		ll right = min(r1, r2 / k_pow);
		res += right - left + 1;
	}

	cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
