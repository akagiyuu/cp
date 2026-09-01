#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	string s, t;
	cin >> s >> t;

	auto f = [&s, &t](int i, int j, char c) {
		return abs(s[i] - c) + abs(s[j] - c) + abs(t[i] - c) + abs(t[j] - c);
	};
	auto fmid = [&s, &t](char c) {
		int n = s.size();
		return abs(s[n / 2] - c) + abs(t[n / 2] - c);
	};

	vector<char> res(n);
	int dist = 0;
	for (int i = 0; i < n / 2; i++) {
		int j = n - 1 - i;
		char mc = 'a';
		for (char c = 'b'; c <= 'z'; c++) {
			if (f(i, j, c) < f(i, j, mc)) {
				mc = c;
			}
		}
		dist += f(i, j, mc);
		res[i] = res[j] = mc;
	}

	if (n % 2 == 1) {
		char mc = 'a';
		for (char c = 'b'; c <= 'z'; c++) {
			if (fmid(c) < fmid(mc)) {
				mc = c;
			}
		}
		dist += fmid(mc);
		res[n / 2] = mc;
	}
	for (auto c : res)
		cout << c << "";
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
