#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll count_odd_sub_array(vector<ll> &a)
{
	ll n = a.size();
    array<ll, 2> count = {1, 0};
	ll sum = 0;
    ll res = 0;

	for (ll i = 0; i < n; i++) {
        sum += a[i];
        sum %= 2;

        res += count[(sum + 1) % 2];
        res %= MOD;
        count[sum] += 1;
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
	cpp_dump(a);

	cout << count_odd_sub_array(a) << "\n";
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll t;
	cin >> t;
	while (t--)
		solve();
}
