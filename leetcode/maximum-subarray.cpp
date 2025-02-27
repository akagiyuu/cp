#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

int maximum_subarray(vector<int> &a)
{
	int partial_sum = a[0];
	int sum = a[0];
	int n = a.size();

	for (int i = 1; i < n; i++) {
		partial_sum = max(partial_sum + a[i], a[i]);
		sum = max(sum, partial_sum);
	}

	return sum;
}

void solve()
{
	int n;
	cin >> n;

	vector<int> a(n);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	cout << maximum_subarray(a) << "\n";
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
