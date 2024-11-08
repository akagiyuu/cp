#include <bits/stdc++.h>
#include <ios>
#include <set>
#include <unordered_set>

using namespace std;

typedef long long ll;

void solve()
{
	int n;
	cin >> n;
	set<int> set;
	for (size_t i = 0; i < n; i++) {
		int x;
		cin >> x;
		set.insert(x);
	}
	cout << set.size() << "\n";
}

int main()
{
	ios_base::sync_with_stdio();
	cin.tie(NULL);
	cout.tie(NULL);
	// ll t;
	// cin >> t;
	// while (t--)
	solve();
}
