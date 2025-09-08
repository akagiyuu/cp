#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	double x, n;
	cin >> x >> n;
	double cur = -1;
	double sum = -1;
	for (double i = 1; i <= n; i++) {
		cur = cur * -x / i;
        sum += cur;
	}
    sum = sum + 2;

    cout << setprecision(7) << sum << "\n";
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
