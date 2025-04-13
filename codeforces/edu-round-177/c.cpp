#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

pair<vector<ll>, vector<ll> > build_comp(vector<ll> &p)
{
	ll n = p.size();

	vector<ll> is_visited(n, false);
	vector<ll> comp(n);
	vector<ll> comp_size;

	ll comp_id = 0;
	for (ll i = 0; i < n; i++) {
		ll cur = p[i];
		if (is_visited[cur])
			continue;
		ll count = 0;
		while (!is_visited[cur]) {
			is_visited[cur] = true;
			comp[cur] = comp_id;
			cur = p[cur];
			count++;
		}
		comp_size.push_back(count);
		comp_id++;
	}

	return make_pair(comp, comp_size);
}

void solve()
{
	ll n;
	cin >> n;

	vector<ll> p(n);
	for (ll i = 0; i < n; i++) {
		cin >> p[i];
		p[i]--;
	}

	auto [comp, comp_size] = build_comp(p);

	set<ll> replaced_comp;
	ll cur_ops = 0;

	for (ll i = 0; i < n; i++) {
		ll d;
		cin >> d;
		d--;

		auto d_comp = comp[d];
		if (replaced_comp.find(d_comp) == replaced_comp.end()) {
			replaced_comp.insert(d_comp);
			cur_ops += comp_size[d_comp];
		}
		cout << cur_ops << " ";
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
