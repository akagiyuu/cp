#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

int consecutive_numbers_sum(int n)
{
	while (n % 2 == 0)
		n /= 2;

	int count = 1;
	for (int i = 2; i * i <= n; i++) {
		if (n % i != 0)
			continue;

		int cur_count = 1;
		while (n % i == 0) {
			n /= i;
			cur_count += 1;
		}

		count *= cur_count;
	}
	if (n > 1) {
		count *= 2;
	}

	return count;
}

void solve()
{
	int n;
	cin >> n;
	cout << consecutive_numbers_sum(n) << "\n";
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
