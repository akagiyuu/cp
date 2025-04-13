#include <algorithm>
#include <bits/stdc++.h>
#include <cpp-dump.hpp>
typedef long long ll;

const ll MOD = 1000000007;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

int trapping_rain_water(vector<int> &a)
{
	int n = a.size();
	int count = 0;
	set<int> a_uniq(a.begin(), a.end());
	int prev_h = 0;
	int i = 0;

	for (auto h : a_uniq) {
		while (a[i] < h)
			i++;
		int prev = i;
		int j = i + 1;

		for (; j < n; j++) {
			if (a[j] >= h) {
				count += (j - prev - 1) * (h - prev_h);
				prev = j;
			}
		}

		prev_h = h;
	}

	return count;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << trapping_rain_water(a) << "\n";
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
