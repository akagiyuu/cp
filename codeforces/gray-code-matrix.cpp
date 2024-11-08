#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

int gray_code(int n)
{
	return n ^ (n >> 1);
}

void solve()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < (1 << m); j++) {
			int cur = (gray_code(i) << m) + gray_code(j);
			cout << cur << " ";
		}
		cout << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
