#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

#define int long long
const int N = 1e6 + 1;
int fib[N];

void build()
{
	fib[0] = 1;
	fib[1] = 1;
	for (int i = 2; i < N; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
}

void solve()
{
	int l, r, k;
	cin >> l >> r >> k;
	int res = 0;
	for (int i = l; i <= r; i++) {
		if (i % k != 0)
			continue;
		res += fib[i] + fib[i - 1];
	}
	cout << res << "\n";
}

signed main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--)
		solve();
}
