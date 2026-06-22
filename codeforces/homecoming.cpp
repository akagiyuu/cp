#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll a, b, p;
	cin >> a >> b >> p;
	string s;
	cin >> s;

	ll n = s.size();
	ll res = n - 1;
	vector<ll> price(n, 0);
	if(s[n - 2] == s[n - 1] && s[n - 2] == 'B') price[n - 2] = a;
	if(s[n - 2] == s[n - 1] && s[n - 2] == 'A') price[n - 2] = b;

	for (ll i = n - 3; i >= 0; i--) {
		price[i] = price[i + 1];
		if (s[i] != s[i + 1] && s[i] == 'B')
			price[i] += a;
		if (s[i] != s[i + 1] && s[i] == 'A')
			price[i] += b;
		if(price[i] > p) break;
		res = i;
	}
	cpp_dump(price);
	cout << res + 1 << "\n";
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
