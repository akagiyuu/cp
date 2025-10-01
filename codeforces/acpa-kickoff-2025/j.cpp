#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 65;

ll cal(vector<ll> &input)
{
	ll n = input.size();
	ll zcount = 0;
	ll sum_msb = 0;
	array<vector<ll>, N> a;
	for (ll i = 0; i < N; i++) {
		a = {};
	}
	for (ll i = 0; i < n; i++) {
		if (input[i] == 0) {
			zcount++;
			continue;
		}
		sum_msb += __lg(input[i]);
		a[__lg(input[i])].push_back(input[i]);
	}

	ll res = zcount * sum_msb;
	ll count = a[0].size();
	for (ll i = 1; i < N; i++) {
		res += i * a[i].size() * count;
		count += a[i].size();
	}
	for (ll i = 0; i < N; i++) {
		ll m = a[i].size();
		if (m <= 1)
			continue;
		for (ll j = 0; j < m; j++) {
			a[i][j] -= 1 << i;
		}

		res += cal(a[i]);
	}

	return res;
}

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);

	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	ll res = cal(a);

	cout << res << "\n";
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
