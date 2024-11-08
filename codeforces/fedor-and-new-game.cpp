#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

bool can_become_friend(int a, int b, int k)
{
	return __builtin_popcount(a ^ b) <= k;
}

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> armies(m + 1);
	for (int i = 0; i < m + 1; i++) {
		cin >> armies[i];
	}

	int count = 0;
	for (int i = 0; i < m; i++) {
		if (can_become_friend(armies[i], armies[m], k))
			count++;
	}
	cout << count << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
