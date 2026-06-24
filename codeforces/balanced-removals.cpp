#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;
typedef array<ll, 3> pt;

const ll MOD = 1000000007;

ll remove_x(ll l, ll r, const vector<pt> &a)
{
}

ll remove_y(ll l, ll r, const vector<pt> &a)
{
}

ll remove_z(ll l, ll r, const vector<pt> &a)
{
}

void solve()
{
	ll n;
	cin >> n;
	vector<pt> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i][2] >> a[i][1] >> a[i][0];
	}
	sort(a.begin(), a.end());
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
