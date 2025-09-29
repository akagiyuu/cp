#include <bits/stdc++.h>
#include <cpp-dump.hpp>
#include <deque>
#include <queue>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

deque<bool> insert_clone(deque<bool> s, ll i, bool val)
{
	s.insert(s.begin() + i, val);
	return s;
}

void print(deque<bool> &s)
{
	for (auto v : s) {
		if (v)
			cout << "1";
		else
			cout << "0";
	}
	cout << "\n";
}

ll solve()
{
	string raw;
	cin >> raw;

	deque<bool> s(raw.size());
	for (ll i = 0; i < raw.size(); i++) {
		s[i] = raw[i] == '1';
	}

	ll ans = 0;
	queue<deque<bool> > q;
	q.push(s);
	while (!q.empty()) {
		auto s = q.front();
        ans++;
		print(s);
		q.pop();
		if (s.size() == 1)
			continue;

        array<bool, 2> vals = { s[0], s[1] };
        s.pop_front();
        s.pop_front();
		ll n = s.size();

		for (ll i = 0; i < 2; i++) {
			if (i == 1 && vals[i] == vals[i - 1])
				break;
			bool val = vals[i];
			ll j = 0;
			while (j <= n) {
				q.push(insert_clone(s, j, val));
				while (j < n && s[j] == val)
					j++;
				j++;
			}
		}
	}

	return ans;
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
