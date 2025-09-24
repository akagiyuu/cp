#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll pow(ll a, ll b)
{
	ll res = 1;

	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b /= 2;
	}

	return res;
}

void solve()
{
	ll n;
	cin >> n;

	ll odd_count = n / 2;
	ll even_count = n - odd_count;

	ll res = pow(4ll, odd_count) * pow(5ll, even_count) % MOD;
	cout << res << "\n";
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
