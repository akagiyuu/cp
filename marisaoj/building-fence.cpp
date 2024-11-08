#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

bool cmp(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
	return b.first < a.first;
}

void solve()
{
	ll n;
	cin >> n;
	vector<pair<ll, ll> > pieces(n);
	for (ll i = 0; i < n; i++) {
		cin >> pieces[i].first;
	}
	for (ll i = 0; i < n; i++) {
		cin >> pieces[i].second;
	}
	sort(pieces.begin(), pieces.end(), cmp);

	vector<ll> max_b(n);
	max_b[n - 1] = pieces[n - 1].second;
	for (ll i = n - 2; i >= 0; i--) {
		max_b[i] = max(max_b[i + 1], pieces[i].second);
	}

	vector<ll> max_swap(n);
	max_swap[0] = pieces[0].second - pieces[0].first;
	for (ll i = 1; i < n; i++) {
		max_swap[i] = max(max_swap[i - 1], pieces[i].second - pieces[i].first);
	}

	ll cur_sum = 0;
	for (ll i = 0; i < n; i++) {
		cur_sum += pieces[i].first;
		ll max_beauty = cur_sum - pieces[i].first + max_b[i];
		max_beauty = max(max_beauty, cur_sum + max_swap[i]);
		cout << max_beauty << "\n";
	}
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
