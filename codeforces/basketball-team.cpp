#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

double solve()
{
	ll n, m, h;
	cin >> n >> m >> h;
	h--;
	double s = 0, ah;
	for (ll i = 0; i < m; i++) {
		if (i == h) {
			cin >> ah;
		} else {
			ll tmp;
			cin >> tmp;
			s += tmp;
		}
	}
	n--;
	ah--;
	if (s + ah < n)
		return -1;
	if (s < n)
		return 1;
	double res = 1;
	for (ll i = 1; i <= ah; i++) {
		res *= (double)(s - n + i) / (double)(s + i);
	}
	res = 1 - res;
	return res;
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << setprecision(10) << solve() << "\n";
}
