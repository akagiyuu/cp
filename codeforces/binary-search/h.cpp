#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, k;
	cin >> n >> k;
	map<ll, ll> m;
	ll x;
	for (ll i = 0; i < n; i++) {
		cin >> x;
		m[x]++;
	}
	vector<pair<ll, ll> > cards(m.begin(), m.end());
	// for (auto [card_num, count] : m) {
	// 	cards.push_back(make_pair(card_num, count));
	// }
	// sort(cards.begin(), cards.end(),
	//      [](const pair<ll, ll> &a, const pair<ll, ll> &b) { return a.first < b.first; });
	n = cards.size();
	// cpp_dump(cards);
	ll cur_count = cards[n - 1].second, cur_k = 1, prev_card_num = cards[n - 1].first, start_i = n - 1;
	ll max_count = cur_count;
	for (ll i = n - 2; i >= 0; i--) {
		if (cards[i].first != prev_card_num - 1) {
			cur_count = cards[i].second;
			cur_k = 1;
			prev_card_num = cards[i].first;
			max_count = max(max_count, cur_count);
			start_i = i;
			continue;
		}
		if (cur_k < k) {
			cur_count += cards[i].second;
			cur_k++;
			prev_card_num = cards[i].first;
			max_count = max(max_count, cur_count);
			continue;
		}

		cur_count += cards[i].second;
		cur_count -= cards[start_i].second;
		start_i--;
		prev_card_num = cards[i].first;
		max_count = max(max_count, cur_count);
	}
	cout << max_count << "\n";
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
