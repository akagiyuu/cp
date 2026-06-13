#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<ll> p(n);
	p[0] = a[0];
	for (ll i = 1; i < n; i++) {
		p[i] = a[i] + p[i - 1];
	}
	ll i = 0;

	ll res = 0;
	map<ll, ll> cnt;
	ll max_cnt = 0;
	while (i < n && a[i] != 0) {
		if (p[i] == 0)
			res++;
		i++;
	}
	while (i < n) {
		if (a[i] == 0) {
			// cout << i << " -> " << max_cnt << "\n";
			res += max_cnt;
			cnt.clear();
			max_cnt = 0;
		}

		cnt[p[i]]++;
		max_cnt = max(max_cnt, cnt[p[i]]);
		i++;
	}
	res += max_cnt;
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
