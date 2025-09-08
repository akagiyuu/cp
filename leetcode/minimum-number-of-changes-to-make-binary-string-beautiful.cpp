#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

int minChanges(string s)
{
	int n = s.size();
	int count = 0;
	for (int i = 0; i < n; i += 2) {
		if (s[i] == s[i + 1])
			continue;
		count++;
	}
}

void solve()
{
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
