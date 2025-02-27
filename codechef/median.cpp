#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		v.push_back(x);
	}
	sort(v.begin(), v.end());
	// nth_element(v.begin(), v.begin() + n / 2 - 1, v.end());
	int index = v.size() / 2;
	if (v.size() % 2 == 0) {
		index--;
	}
	// int e = v[(n - 1) / 2];
	cout << v[index];
}
