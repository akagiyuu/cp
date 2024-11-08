#include <bits/stdc++.h>
// #include "/home/yuu/Code/competitive_programming/cpp-dump/cpp-dump.hpp"

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	string s;
	cin >> s;
	int n = s.length();
	int is_visited[26] = { false };
	char cur = 'a' - 1;
	for (int i = 0; i < n; i++) {
		if (is_visited[s[i] - 'a']) {
			continue;
		}
		if (s[i] != cur + 1) {
			cout << "NO";
			return;
		}
		cur = s[i];
		is_visited[s[i] - 'a'] = true;
	}
	cout << "YES";
}

int main()
{
	solve();
}
