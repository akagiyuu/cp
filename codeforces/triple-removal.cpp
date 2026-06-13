#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve()
{
	ll n, q;
	cin >> n >> q;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<array<ll, 2> > cnt(n, { 0, 0 });
	vector<ll> diff_cnt(n, 0);
	for (ll i = 0; i < n; i++) {
		if (i > 0)
			cnt[i] = cnt[i - 1];
		cnt[i][a[i]]++;
		if (i > 0) {
			diff_cnt[i] = diff_cnt[i - 1];
			diff_cnt[i] += a[i] != a[i - 1];
		}
	}

	while (q--) {
		ll l, r;
		cin >> l >> r;
		l--;
		r--;

		auto sub_cnt = cnt[r];
		if (l > 0) {
			sub_cnt[0] -= cnt[l - 1][0];
			sub_cnt[1] -= cnt[l - 1][1];
		}
		if (sub_cnt[0] % 3 != 0 || sub_cnt[1] % 3 != 0) {
			cout << -1 << "\n";
			continue;
		}

		ll res = sub_cnt[0] / 3 + sub_cnt[1] / 3;
		if (diff_cnt[r] - diff_cnt[l] == (r - l))
			res += 1;
		cout << res << "\n";
	}
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
