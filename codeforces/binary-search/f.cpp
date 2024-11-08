#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll a, b, x, y;
	cin >> a >> b >> x >> y;
	ll g = gcd(x, y);
	x /= g;
	y /= g;
	ll max_t = min(a / x, b / y);
	x *= max_t;
	y *= max_t;
	cout << x << " " << y << "\n";
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
