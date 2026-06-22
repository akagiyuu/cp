#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

bool ask(const deque<char> &s)
{
	cout << "? ";
	for (auto c : s)
		cout << c;
	cout << endl;
	bool res;
	cin >> res;
	return res;
}

void solve()
{
	ll n;
	cin >> n;
	deque<char> res;
	while (res.size() < n) {
		res.push_back('0');
		if (ask(res))
			continue;
		res.pop_back();

		res.push_back('1');
		if (ask(res))
			continue;
		res.pop_back();
		break;
	}
	while (res.size() < n) {
		res.push_front('0');
		if (ask(res))
			continue;
		res.pop_front();

		res.push_front('1');
	}

	cout << "! ";
	for (auto c : res)
		cout << c;
	cout << endl;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
		solve();
}
