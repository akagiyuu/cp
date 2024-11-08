#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	int n;
	cin >> n;
	int len = 1ll << n;
	for (int i = 0; i < len; i++) {
		int cur = (i ^ (i >> 1));
		for (int i = n - 1; i >= 0; i--) {
			cout << ((cur >> i) & 1);
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
