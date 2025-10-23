#include <bits/stdc++.h>

using namespace std;

#define int long long
const int N = 1e5;

vector<int> pr;

void build()
{
	bitset<N> sieve;
	sieve.set(0, 1);
	sieve.set(1, 1);
	for (int i = 2; i < N; i++) {
		if (sieve[i])
			continue;
		pr.push_back(i);
		for (int j = 2 * i; j < N; j += i) {
			sieve.set(j, 1);
		}
	}
}

set<int> s;
bool solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	s.clear();
	for (auto x : a) {
		for (auto p : pr) {
			if (p * p > x)
				break;
			if (x % p != 0)
				continue;
			if (s.count(p) == 1)
				return true;
			s.insert(p);
			while (x % p == 0) {
				x /= p;
			}
		}
		if (x > 1) {
			if (s.count(x) == 1)
				return true;
			s.insert(x);
		}
	}

	return false;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	build();

	int t;
	cin >> t;
	while (t--) {
		if (solve())
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}
