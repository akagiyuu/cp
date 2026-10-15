#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

int area(int i, int j, int k)
{
	cout << 1 << ' ' << i << ' ' << j << ' ' << k << endl;
	int res;
	cin >> res;
	return res;
}

int cross(int i, int j, int k)
{
	cout << 2 << ' ' << i << ' ' << j << ' ' << k << endl;
	int res;
	cin >> res;
	return res;
}

void solve()
{
	int n;
	cin >> n;
	int a = 1, b = 2;
	vector<int> upper, lower;
	vector<int> dist(n + 1, 0);
	for (int i = 3; i <= n; i++) {
		int cr = cross(a, b, i);
		assert(cr != 0);
		if (cr > 0)
			upper.push_back(i);
		else
			lower.push_back(i);
		dist[i] = area(a, b, i);
	}

	if (!upper.empty()) {
		int mx = upper[0];
		for (auto i : upper)
			if (dist[i] > dist[mx])
				mx = i;
		vector<int> left, right;
		for (auto i : upper) {
			if (i == mx) {
				left.push_back(i);
				continue;
			}
			int cr = cross(a, mx, i);
			assert(cr != 0);
			if (cr > 0)
				left.push_back(i);
			else
				right.push_back(i);
		}
		sort(left.begin(), left.end(), [&](int i, int j) { return dist[i] > dist[j]; });
		sort(right.begin(), right.end(), [&](int i, int j) { return dist[i] < dist[j]; });
		upper.clear();
		for (auto i : right)
			upper.push_back(i);
		for (auto i : left)
			upper.push_back(i);
	}
	if (!lower.empty()) {
		int mx = lower[0];
		for (auto i : lower)
			if (dist[i] > dist[mx])
				mx = i;
		vector<int> left, right;
		for (auto i : lower) {
			if (i == mx) {
				left.push_back(i);
				continue;
			}
			int cr = cross(a, mx, i);
			assert(cr != 0);
			if (cr < 0)
				left.push_back(i);
			else
				right.push_back(i);
		}
		sort(left.begin(), left.end(), [&](int i, int j) { return dist[i] < dist[j]; });
		sort(right.begin(), right.end(), [&](int i, int j) { return dist[i] > dist[j]; });
		lower.clear();
		for (auto i : left)
			lower.push_back(i);
		for (auto i : right)
			lower.push_back(i);
	}
	cout << 0 << ' ';
	cout << a << ' ';
	for (auto i : lower)
		cout << i << ' ';
	cout << b << ' ';
	for (auto i : upper)
		cout << i << ' ';
	cout << endl;
}

signed main()
{
	solve();
}
