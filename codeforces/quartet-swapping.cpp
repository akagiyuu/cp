#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

pair<ll, ll> get_maxes(vector<ll> &a)
{
	ll n = a.size();
	pair<ll, ll> max_vals = { max(a[0], a[1]), min(a[0], a[1]) };
	for (ll i = 2; i < n; i++) {
		ll v = a[i];
		if (v >= max_vals.first) {
			max_vals.second = max_vals.first;
			max_vals.first = v;
			continue;
		}
		if (v >= max_vals.second) {
			max_vals.second = v;
			continue;
		}
	}

	return max_vals;
}

vector<ll> solve()
{
	ll n;
	cin >> n;
	vector<ll> even((n + 1) / 2), odd(n / 2);
	for (ll i = 0; i < n; i++) {
		if (i % 2 == 0)
			cin >> even[i / 2];
		else
			cin >> odd[i / 2];
	}

	auto maxes_even = get_maxes(even);
	bool swap_even = find(even.rbegin(), even.rend(), maxes_even.first) >
			 find(even.rbegin(), even.rend(), maxes_even.second);
	auto maxes_odd = get_maxes(odd);
	bool swap_odd = find(odd.rbegin(), odd.rend(), maxes_odd.first) >
			find(odd.rbegin(), odd.rend(), maxes_odd.second);
	// cpp_dump(maxes_even, swap_even);
	// cpp_dump(maxes_odd, swap_odd);

	sort(odd.begin(), odd.end());
	sort(even.begin(), even.end());

	vector<ll> res(n);
	for (ll i = 0; i < n; i++) {
		if (i % 2 == 0)
			res[i] = even[i / 2];
		else
			res[i] = odd[i / 2];
	}
	if (swap_even == swap_odd)
		return res;

	if (n % 2 == 0) {
		res[n - 4] = maxes_even.second;
		res[n - 2] = maxes_even.first;
		res[n - 3] = maxes_odd.first;
		res[n - 1] = maxes_odd.second;
	} else {
		res[n - 4] = maxes_odd.second;
		res[n - 2] = maxes_odd.first;
		res[n - 3] = maxes_even.first;
		res[n - 1] = maxes_even.second;
	}

	return res;
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		auto a = solve();
		for (auto x : a) {
			cout << x << " ";
		}
		cout << "\n";
	}
}
