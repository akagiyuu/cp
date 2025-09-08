#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

vector<int> xorQueries(vector<int> &a, vector<vector<int> > &q)
{
	auto n = a.size();
	auto m = q.size();
	vector<int> p(n);
	p[0] = a[0];

	for (auto i = 1; i < n; i++) {
		p[i] = a[i] ^ p[i - 1];
	}

	vector<int> res(m);
	for (int i = 0; i < m; i++) {
		auto left = q[i][0];
		auto right = q[i][1];
		res[i] = left == 0 ? p[right] : p[right] - p[left - 1];
	}
	return res;
}

void solve()
{
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
