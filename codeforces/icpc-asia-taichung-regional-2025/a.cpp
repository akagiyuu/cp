#include <bits/stdc++.h>

using namespace std;

void solve()
{
	vector<int> a(3);
	for (int i = 0; i < 3; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	if (a[2] - a[0] >= 10) {
		cout << "check again\n";
		return;
	}

	cout << "final " << a[1] << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
