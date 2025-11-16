#include <algorithm>
#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve()
{
	int n, a, b;
	cin >> n >> a >> b;
	a--;
	b--;
	vector<int> p;
	if (a > b)
		swap(a, b);
	while (n) {
		p.push_back(n % 10);
		n /= 10;
	}
	reverse(p.begin(), p.end());
	for (int i = 0; i < a; i++) {
		next_permutation(p.begin(), p.end());
	}
	auto pa = p;
	for (int i = 0; i < b - a; i++) {
		next_permutation(p.begin(), p.end());
	}
	auto pb = p;
	int cnt = 0;
	for (int i = 0; i < (int)p.size(); i++) {
		// cout << pa[i] << " " << pb[i] << "\n";
		if (pa[i] == pb[i])
			cnt++;
	}
	cout << cnt << "A" << p.size() - cnt << "B\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
