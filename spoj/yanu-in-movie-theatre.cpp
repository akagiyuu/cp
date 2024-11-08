#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	double n, m;
	while (true) {
		cin >> n >> m;
		if (n == 0 && m == 0)
			break;
		double res = max((m + 1 - n) / (m + 1), (double)0);
		res = round(res * 1e6) / 1e6;
        printf("%.6lf\n", res);
	}
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// int t;
	// cin >> t;
	// while (t--)
	solve();
}
