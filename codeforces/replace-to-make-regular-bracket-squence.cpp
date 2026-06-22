#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

bool is_open(char c)
{
	return c == '<' || c == '{' || c == '[' || c == '(';
}
bool is_matching(char l, char r)
{
	return (l == '<' && r == '>') || (l == '{' && r == '}') || (l == '[' && r == ']') || (l == '(' && r == ')');
}

void solve()
{
	string s;
	cin >> s;

	stack<char> st;
	ll res = 0;
	for (auto c : s) {
		if (is_open(c)) {
			st.push(c);
			continue;
		}
		if (st.empty()) {
			cout << "Impossible\n";
			return;
		}
		char l = st.top();
		st.pop();
		if (!is_matching(l, c))
			res++;
	}
	if (!st.empty()) {
		cout << "Impossible\n";
		return;
	}
	cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
