#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 1000000007;

bool ask(int i, int j)
{
	cout << "? " << i << " " << j << endl;
	int contain;
	cin >> contain;
	assert(contain != -1);
	return contain == 1;
}

void solve()
{
	int n;
	cin >> n;
	n--;
	vector<int> p(n + 1, -1);
	p[1] = 0;

	int i = 2;
	queue<int> paths;
	for (; i <= n; i++) {
		if (ask(1, i)) {
			p[i] = 0;
			paths.push(i);
		} else {
			p[i] = 1;
			paths.push(i);
			i++;
			break;
		}
	}

	for (; i <= n; i++) {
		while (ask(i, paths.front())) {
			paths.pop();
		}
		p[i] = paths.front();
		paths.pop();
		paths.push(i);
	}
	cout << "! ";
	for (int i = 1; i <= n; i++) {
		cout << p[i] << " ";
	}
	cout << endl;
}

signed main()
{
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;
	while (t--)
		solve();
}
