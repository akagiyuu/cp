#include <bits/stdc++.h>
#include <climits>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, res = 0;
	cin >> n;

	vector<pair<ll, ll> > p(n);
	for (ll i = 0; i < n; i++) {
		cin >> p[i].first >> p[i].second;
		res += p[i].second - p[i].first;
	}

	vector<pair<ll, pair<ll, ll> > > sum(n);
	for (ll i = 0; i < n; i++) {
		sum[i].first = p[i].first + p[i].second;
		sum[i].second = p[i];
	}
	sort(sum.begin(), sum.end(),
	     [](pair<ll, pair<ll, ll> > a, pair<ll, pair<ll, ll> > b) { return a.first < b.first; });

	for (ll i = 0; i < n / 2; i++) {
		res -= sum[i].first;
	}
	for (ll i = 0; i < n; i++) {
		res += p[i].second;
	}

	if (n % 2 == 0) {
		cout << res << "\n";
		return;
	}

	ll max_diff = LONG_LONG_MIN;
	for (ll i = n / 2; i < n; i++) {
		ll r = sum[i].second.second;
		max_diff = max(max_diff, -r);
	}

	for (ll i = 0; i < n / 2; i++) {
		ll cur = -sum[n / 2].first + sum[i].first - sum[i].second.second;
		max_diff = max(max_diff, cur);
	}
	res += max_diff;

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
