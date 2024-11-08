#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

bool cmp(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
	return a.first < b.first;
}

void solve()
{
	ll n, d;
	cin >> n >> d;
	vector<pair<ll, ll> > a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second;
	}
	sort(a.begin(), a.end(), cmp);
	vector<ll> prefix_friendship(n);
	prefix_friendship[0] = a[0].second;
	for (ll i = 1; i < n; i++) {
		prefix_friendship[i] = prefix_friendship[i - 1] + a[i].second;
	}
	auto cal_friendship = [prefix_friendship](ll i, ll j) {
		if (i > j)
			return 0ll;
		return prefix_friendship[j] - (i == 0 ? 0 : prefix_friendship[i - 1]);
	};

	ll max_friendship = 0;
	for (ll i = 0; i < n; i++) {
		ll cur_money = a[i].first;
		ll j = lower_bound(a.begin(), a.end(), make_pair(cur_money + d, 0), cmp) - a.begin();
		ll cur_friendship = cal_friendship(i, j - 1);
		max_friendship = max(max_friendship, cur_friendship);
	}
	cout << max_friendship;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
