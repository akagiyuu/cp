#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve()
{
	string s;
	cin >> s;
	int n = s.size();

	vector<char> a;
	vector<int> pre, post;

	int cnt = 0;
	int i = -1;

	for (auto c : s) {
		if (c == '+') {
			cnt++;
		} else {
			a.push_back(c);
			pre.push_back(0);
			post.push_back(0);

			i++;
			if (i == 0) {
				pre[i] = cnt / 2;
			} else {
				if (cnt == 3) {
					post[i - 1] = 1;
				}
				if (cnt == 5) {
					post[i - 1] = 1;
					pre[i] = 1;
				}
			}

			cnt = 0;
		}
	}

	post[i] = cnt / 2;

	string res;
	for (int i = 0; i < pre.size(); i++) {
		if (i > 0)
			res.push_back('+');

		res.push_back('(');
		if (pre[i])
			res += "++";
		res.push_back(a[i]);
		if (post[i])
			res += "++";
		res.push_back(')');
	}

	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
