#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, k, x;
	cin >> n >> k >> x;

	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}

	ll total_sum = 0;
	for (ll i = 0; i < n; i++) {
		total_sum += a[i];
	}

	ll count = 0;
	ll sum = 0;
	for (ll i = n - 1; i >= 0; i--) {
		sum += a[i];
		ll start_k = (max(x - sum, 0ll) + total_sum - 1) / total_sum;
		count += max(k - start_k, 0ll);
	}

	cout << count << "\n";
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
