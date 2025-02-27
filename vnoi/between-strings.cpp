#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll q, n, p;
	cin >> q >> n >> p;
	vector<ll> ds(n);
	for (ll i = 0; i < n; i++) {
		cin >> ds[i];
	}
	string s, w;
	cin >> s >> w;
	vector<short> a(q), b(q);

	ll left = 0, right = 0;
	ll res = 0;
	ll diff_start = 0;

	auto cal = [](int d) {

	};

	for (ll i = 0; i < q; i++) {
		char choice = w[i];
		if (choice == 'A') {
			a[left] = s[i] - 'a';
			if (a[left] == b[left])
				diff_start = left + 1;
			left++;
		} else {
			b[right] = s[i] - 'a';
			if (b[right] == a[right])
				diff_start = right + 1;
			right++;
		}
		ll sum = 0;
		for (auto d : ds) {
			sum = (sum + cal(d)) % p;
		}
		res = res ^ (sum * (i + 1));
	}
	cout << res;
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
