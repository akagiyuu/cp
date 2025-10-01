#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll n = 4;
typedef array<array<ll, n>, n> Grid;

const ll MOD = 1000000007;

bool is_valid(Grid &g)
{
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			if (g[i][j] > 0)
				continue;
		}
	}
}

void solve()
{
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
