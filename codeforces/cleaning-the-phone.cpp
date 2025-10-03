#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, k;
	cin >> n >> k;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
	}

	vector<ll> idx;
	vector<pair<ll, ll> > s;
	if (a[0] > 0) {
		idx.push_back(0);
		s.push_back({ 0, 0 });
	}

	for (ll i = 0; i < n - 1; i++) {
		if (a[i] + 1 == a[i + 1]) {
			continue;
		}
		s.push_back({ a[i] - i, i + 1 });
		idx.push_back(a[i] - i);
	}
	s.push_back({ a[n - 1] - n + 1, n });
	idx.push_back(a[n - 1] - n + 1);

	ll i = 0;
	ll x = 0;
	while (k--) {
		x = upper_bound(idx.begin() + x, idx.end(), i) - idx.begin() - 1;
		i += s[x].second;
		if (x == idx.size() - 1)
			break;
	}
	if (k >= 0)
		i = i + k * n;
	i++;
	cout << i << "\n";
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
