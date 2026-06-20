#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n), b(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i < n; i++) {
		cin >> b[i];
	}

	vector<pair<ll, ll> > c(n);
	for (ll i = 0; i < n; i++) {
		c[i] = { i, a[i] - b[i] };
	}
	sort(c.begin(), c.end(), [](const pair<ll, ll> &a, const pair<ll, ll> &b) {
		if (a.second != b.second)
			return a.second > b.second;
		return a.first < b.first;
	});
	ll cnt = 0;
	for (ll i = 0; i < n; i++) {
		if (c[i].second == c[0].second)
			cnt++;
		else
			break;
	}
	cout << cnt << "\n";
	for (ll i = 0; i < cnt; i++) {
		cout << c[i].first + 1 << " ";
	}
	cout << "\n";
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
