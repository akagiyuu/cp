#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, t;
	cin >> n >> t;

	vector<ll> ws(n), vs(n);
	for (ll i = 0; i < n; i++) {
		cin >> ws[i];
	}

	for (ll i = 0; i < n; i++) {
		cin >> vs[i];
	}

	vector<vector<ll> > dp(t + 1, vector<ll>(n));

	for (ll i = 0; i < n; i++) {
		dp[0][i] = 0;
	}

	for (ll max_w = 0; max_w <= t; max_w++) {
		dp[max_w][0] = max_w >= ws[0] ? vs[0] : 0;
	}

	ll res = 0;
	for (ll max_w = 1; max_w <= t; max_w++) {
		for (ll i = 1; i < n; i++) {
			dp[max_w][i] = dp[max_w][i - 1];
			if (max_w >= ws[i]) {
				dp[max_w][i] = max(dp[max_w][i], dp[max_w - ws[i]][i - 1] + vs[i]);
			}
		}
		res = max(res, dp[max_w][n - 1]);
	}
	cout << res << "\n";
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
