#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

struct SegmentTree {
	ll n;
	vector<ll> t;

	void build(const vector<ll> &a, ll v, ll tl, ll tr)
	{
		if (tl == tr) {
			t[v] = a[tl];
			return;
		}
		ll tmid = (tl + tr) / 2;
		build(a, 2 * v, tl, tmid);
		build(a, 2 * v + 1, tmid + 1, tr);
		t[v] = t[2 * v] + t[2 * v + 1];
	}
	void build(const vector<ll> &a)
	{
		n = a.size();
		t.resize(4 * n, 0);
		build(a, 1, 0, n - 1);
	}

	ll get(ll v, ll tl, ll tr, ll l, ll r)
	{
		if (l > r)
			return 0;
		if (tl == l && tr == r) {
			return t[v];
		}
		ll tmid = (tl + tr) / 2;
		return get(2 * v, tl, tmid, l, min(r, tmid)) + get(2 * v + 1, tmid + 1, tr, max(tmid + 1, l), r);
	}

	ll get(ll l, ll r)
	{
		return get(1, 0, n - 1, l, r);
	}

	void update(ll v, ll tl, ll tr, ll pos, ll x)
	{
		if (tl == tr) {
			t[v] = x;
			return;
		}

		ll tmid = (tl + tr) / 2;
		if (pos <= tmid)
			update(2 * v, tl, tmid, pos, x);
		else
			update(2 * v + 1, tmid + 1, tr, pos, x);
		t[v] = t[2 * v] + t[2 * v + 1];
	}

	void update(ll pos, ll x)
	{
		update(1, 0, n - 1, pos, x);
	}
};

ll n;
vector<ll> a;
unordered_map<ll, vector<ll> > mp;
unordered_map<ll, SegmentTree> trees;

void process_first(ll p)
{
	if (a[p] == a[p + 1])
		return;
	ll v1 = p * p;
	ll v2 = (p + 1) * (p + 1);
	auto p_1 = lower_bound(mp[a[p]].begin(), mp[a[p]].end(), v1);
	trees[a[p]].update(p_1 - mp[a[p]].begin(), v2);
	*p_1 = v2;
	auto p_2 = lower_bound(mp[a[p + 1]].begin(), mp[a[p + 1]].end(), v2);
	trees[a[p + 1]].update(p_2 - mp[a[p + 1]].begin(), v1);
	*p_2 = v1;
	swap(a[p], a[p + 1]);
}

ll process_second(ll l, ll r, ll x)
{
	if (mp.find(x) == mp.end()) {
		return 0;
	}
	ll length = mp[x].size();
	if (length == 0)
		return 0;
	// cpp_dump("2");
	// cpp_dump(l, r, x);
	// cpp_dump(mp[x]);
	ll start = lower_bound(mp[x].begin(), mp[x].end(), l * l) - mp[x].begin();
	if (start >= length)
		return 0;
	ll end = upper_bound(mp[x].begin(), mp[x].end(), r * r) - mp[x].begin() - 1;
	if (end < 0)
		return 0;
	if (start > end)
		return 0;

	return trees[x].get(start, end);
}

ll process_third(ll l, ll r, ll x)
{
	if (mp.find(x) == mp.end()) {
		return 0;
	}

	// cpp_dump("3");
	// cpp_dump(l, r, x);
	// cpp_dump(mp[x]);
	// cpp_dump(trees[x].t);
	return trees[x].get(l, r);
}

void solve()
{
	ll q, last = 0;
	cin >> n >> q;
	a.resize(n + 1, 0);
	for (ll i = 1; i <= n; i++) {
		cin >> a[i];
	}
	// cpp_dump(a);
	for (ll i = 1; i <= n; i++) {
		mp[a[i]].push_back(i * i);
	}
	for (auto [val, positions] : mp) {
		trees[val].build(positions);
	}

	while (q--) {
		short t;
		cin >> t;
		switch (t) {
		case 1: {
			ll p;
			cin >> p;
			p = (p + last - 1 + n - 1) % (n - 1) + 1;
			process_first(p);
			break;
		}
		case 2: {
			ll l, r, x;
			cin >> l >> r >> x;
			l = (l + last - 1) % n + 1;
			r = (r + last - 1) % n + 1;
			if (l > r)
				swap(l, r);
			x = (x + last - 1) % n + 1;
			last = process_second(l, r, x);
			cout << last << "\n";
			break;
		}
		case 3: {
			ll l, r, x;
			cin >> l >> r >> x;
			l = (l + last - 1) % n;
			r = (r + last - 1) % n;
			if (l > r)
				swap(l, r);
			x = (x + last - 1) % n + 1;
			last = process_third(l, r, x);
			cout << last << "\n";
			break;
		}
		}
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
