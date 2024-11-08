#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	int n;
	cin >> n;
	int prev = 0;
	int prev_count[2] = { 0, 0 };
	int res = 0;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x == prev) {
			prev_count[1]++;
			continue;
		}
		res = max(res, min(prev_count[0], prev_count[1]) * 2);
		prev_count[0] = prev_count[1];
		prev_count[1] = 1;
		prev = x;
	}
	res = max(res, min(prev_count[0], prev_count[1]) * 2);
	cout << res;
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
