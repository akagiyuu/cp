#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll count_step(ll a, ll b)
{
	if (a == 0)
		return 0;
	return count_step(b, abs(a - b)) + 1;
}

ll count_stepn(vector<ll> &a, vector<ll> &b)
{
	ll res = 0;
	ll n = a.size();
	while (true) {
		bool exit = true;
		ll x = a[0];
		for (ll i = 1; i < n; i++) {
			if (a[i] != x) {
				exit = false;
				break;
			}
		}
		if (exit)
			break;
		res++;
		for (ll i = 0; i < n; i++) {
			tie(a[i], b[i]) = make_pair(b[i], abs(a[i] - b[i]));
		}
        cpp_dump(res);
        cpp_dump(a);
        cpp_dump(b);
	}
	return res;
}

bool solve()
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
	// cpp_dump(count_stepn(a, b));
	// for (ll i = 0; i < n; i++) {
	// 	cout << count_step(a[i], b[i]) << " ";
	// }
	// cout << "\n";

	ll r = count_step(a[0], b[0]) % 3;
	for (ll i = 1; i < n; i++) {
		if (count_step(a[i], b[i]) % 3 != r)
			return false;
	}

	return true;
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		if (solve()) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
}
