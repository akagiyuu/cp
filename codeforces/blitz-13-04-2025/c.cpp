#include <bits/stdc++.h>
#include <cpp-dump.hpp>
#include <utility>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

bool is_non_descreasing(vector<ll> &a)
{
	ll n = a.size();

	for (ll i = 0; i < n - 1; i++) {
		if (a[i] > a[i + 1]) {
			return false;
		}
	}

	return true;
}

bool is_good(vector<vector<ll> > &grid, int first, int second)
{
	ll n = grid.size();

	for (ll i = 0; i < n; i++) {
		swap(grid[i][first], grid[i][second]);
		if (!is_non_descreasing(grid[i])) {
			swap(grid[i][first], grid[i][second]);
			return false;
		} else {
			swap(grid[i][first], grid[i][second]);
		}
	}

	return true;
}

void solve()
{
	ll n, m;
	cin >> n >> m;

	vector<vector<ll> > grid(n, vector<ll>(m));
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}

	if (is_good(grid, 0, 0)) {
		cout << "1 1\n";
		return;
	}

	for (ll i = 0; i < n; i++) {
		for (ll j = i + 1; j < n; j++) {
			if (is_good(grid, i, j)) {
				cout << i + 1 << " " << j + 1 << "\n";
				return;
			}
		}
	}

	cpp_dump(grid);

	cout << "-1\n";
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
