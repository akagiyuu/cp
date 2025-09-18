#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, score = 0;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		if (i % 2 == 0)
			score += a[i];
		else
			score -= a[i];
	}

	// even l
	ll prefix = LONG_LONG_MIN;
	ll max_diff = (n - 1) / 2 * 2;
	ll l = n % 2 == 0 ? n - 2 : n - 3;
	for (; l >= 0; l -= 2) {
		ll val_l = -2 * a[l] - l;
		prefix = max(prefix, 2 * a[l + 1] + (l + 1));
		max_diff = max(max_diff, prefix + val_l);
	}

	// odd l
	prefix = LONG_LONG_MIN;
	l = n % 2 == 0 ? n - 3 : n - 2;
	for (; l >= 0; l -= 2) {
		ll val_l = 2 * a[l] - l;
		prefix = max(prefix, l + 1 - 2 * a[l + 1]);
		max_diff = max(max_diff, prefix + val_l);
	}

	score = max(score, score + max_diff);
	cout << score << "\n";
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
