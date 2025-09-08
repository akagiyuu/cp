#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;

	vector<pair<ll, ll> > ps(n);

	for (ll i = 0; i < n; i++) {
		cin >> ps[i].first >> ps[i].second;
	}

	sort(ps.begin(), ps.end(), [](pair<ll, ll> a, pair<ll, ll> b) {
		if (a.first != b.first) {
			return a.first < b.first;
		}

		return a.second < b.second;
	});

	pair<ll, ll> cur = { 0, 0 };
	string res;
	for (ll i = 0; i < n; i++) {
		ll dx = ps[i].first - cur.first;
		ll dy = ps[i].second - cur.second;
		if (dx < 0 || dy < 0) {
			cout << "NO\n";
			return;
		}
		for (ll i = 0; i < dx; i++) {
			res.push_back('R');
		}
		for (ll i = 0; i < dy; i++) {
			res.push_back('U');
		}
		cur = ps[i];
	}
	cout << "YES\n";
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
