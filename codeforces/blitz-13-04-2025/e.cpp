#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll find(string &s, char c)
{
	ll n = s.length();

	for (ll i = 0; i < n; i++) {
		if (s[i] == c)
			return i;
	}

	return -1;
}

void solve()
{
	ll n, t;
	cin >> n >> t;

	string s;
	cin >> s;

	ll dot_pos = find(s, '.');

	auto prev = [dot_pos](ll i) {
		if (i - 1 == dot_pos)
			return i - 2;
		else
			return i - 1;
	};

	ll end = -1;
	for (ll i = dot_pos + 1; i <= n - 1; i++) {
		if (s[i] - '0' < 5)
			continue;
		end = i;
		break;
	}
	if (end == -1) {
		cout << s << "\n";
		return;
	}

	while (t--) {
		if (end <= dot_pos - 1)
			break;
		if (s[end] - '0' < 5)
			break;

		while (prev(end) >= 0 && s[prev(end)] == '9') {
			s[prev(end)] = '0';
			end = prev(end);
		}

		if (prev(end) >= 0) {
			s[prev(end)]++;
			end = prev(end);
		} else {
            break;
        }
	}

	if (s[0] == '0')
		cout << "1";

	end = max(end, dot_pos - 1);
	for (ll i = 0; i <= end; i++) {
		cout << s[i];
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
