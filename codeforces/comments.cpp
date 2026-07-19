#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>

const int MOD = 1000000007;
const int N = 1e6;

void solve()
{
	vector<string> decode;
	decode.push_back("");
	vector<vector<int> > c(N);
	stack<pi> prev;
	prev.push({ 0, LLONG_MAX });

	int i = 1;
	string s, scnt;
	while (std::getline(cin, s, ',')) {
		decode.push_back(s);

		std::getline(cin, scnt, ',');
		int cnt = stoi(scnt);

		auto [p, pcnt] = prev.top();
		prev.pop();
		pcnt--;
		if (pcnt > 0)
			prev.push({ p, pcnt });
		c[p].push_back(i);

		if (cnt > 0)
			prev.push({ i, cnt });
		i++;
	}
	vector<vector<int> > layers;
	queue<pi> q;
	q.push({ 0, -1 });
	while (!q.empty()) {
		auto [u, l] = q.front();
		q.pop();
		if (u != 0) {
			if ((int)layers.size() == l)
				layers.push_back(vector<int>());
			layers[l].push_back(u);
		}
		for (auto v : c[u]) {
			q.push({ v, l + 1 });
		}
	}

	cout << layers.size() << "\n";
	for (auto l : layers) {
		for (auto u : l) {
			cout << decode[u] << " ";
		}
		cout << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
