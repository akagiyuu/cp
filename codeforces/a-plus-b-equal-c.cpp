#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 26;
string a, b, c;
vector<char> letters;
vector<int> values;
int ra, rb, rc;

int decode(const string &s)
{
	int res = 0;
	int p = 1;
	int last = -1;
	for (auto c : s) {
		int d = values[find(letters.begin(), letters.end(), c) - letters.begin()];
		res += d * p;
		last = d;
		p *= 10;
	}
	if (last == 0)
		return -1;
	return res;
}

int dfs(int i)
{
	if (i == (int)letters.size()) {
		int cur_a = decode(a);
		int cur_b = decode(b);
		int cur_c = decode(c);
		if (cur_a == -1 || cur_b == -1 || cur_c == -1 || cur_a + cur_b != cur_c)
			return 0;
		ra = cur_a;
		rb = cur_b;
		rc = cur_c;
		return 1;
	}

	int res = 0;
	for (int x = 0; x <= 9; x++) {
		if (find(values.begin(), values.end(), x) != values.end())
			continue;
		values.push_back(x);
		res += dfs(i + 1);
		values.pop_back();
	}
	return res;
}

void solve()
{
	cin >> a >> b >> c;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	reverse(c.begin(), c.end());

	vector<bool> exist(N, false);
	for (auto x : a)
		exist[x - 'A'] = true;
	for (auto x : b)
		exist[x - 'A'] = true;
	for (auto x : c)
		exist[x - 'A'] = true;
	letters.clear();
	for (int i = 0; i < N; i++) {
		if (exist[i])
			letters.push_back(i + 'A');
	}

	values.clear();
	int cnt = dfs(0);
	cout << cnt << "\n";
	if (cnt > 0) {
		cout << ra << "\n";
		cout << rb << "\n";
		cout << rc << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
