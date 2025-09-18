#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, score = 0;
	short turn = 0;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		if (i % 2 == 0)
			score += a[i];
		else
			score -= a[i];
	}
	if (n == 1) {
		cout << a[0] << "\n";
		return;
	}

	auto cal_l = [a](ll l) {
		if (l % 2 == 0)
			return 2 * a[l] - l;
		else
			return -2 * a[l] - l;
	};
	auto cal_r = [a](ll r) {
		if (r % 2 == 0)
			return -2 * a[r] + r;
		else
			return 2 * a[r] + r;
	};

	for (ll round = 0; round < 5; round++) {
		short turn = round % 2;
		ll choose_l = n - 2, choose_r = n - 1;
		ll suffix_r = n - 1;
		ll suffix = cal_r(suffix_r);

		for (ll l = n - 2; l >= 0; l--) {
			ll left = cal_l(l);
			if (turn == 0) {
				if (cal_r(l + 1) > suffix) {
					suffix = cal_r(l + 1);
					suffix_r = l + 1;
				}

				if (left + suffix > cal_l(choose_l) + cal_r(choose_r)) {
					choose_l = l;
					choose_r = suffix_r;
				}
			} else {
				if (cal_r(l + 1) < suffix) {
					suffix = cal_r(l + 1);
					suffix_r = l+ 1;
				}

				if (left + suffix < cal_l(choose_l) + cal_r(choose_r)) {
					choose_l = l;
					choose_r = suffix_r;
				}
			}
		}

		ll cur = score + cal_l(choose_l) + cal_r(choose_r);
        cpp_dump(turn);
        cpp_dump(choose_l, choose_r);
        cpp_dump(cur);
		if (turn == 0) {
			if (cur <= score) {
				break;
			}
		} else {
			if (cur >= score) {
				break;
			}
		}

		score = cur;
		tie(a[choose_l], a[choose_r]) = make_pair(a[choose_r], a[choose_l]);
	}
    cout << score << "\n";
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
