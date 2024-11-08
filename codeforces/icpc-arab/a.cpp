#include <bits/stdc++.h>

const int MOD = 1000000007;

using namespace std;

struct Hash {
	size_t operator()(const array<int, 11> &a) const
	{
		size_t res = 0;
		for (int i = 0; i < 11; ++i) {
			res ^= a[i] + 0x9e3779b9 + (res << 6) + (res >> 2);
		}
		return res;
	}

	size_t operator()(const pair<int, int> &p) const
	{
		return p.first ^ p.second;
	}
};

int recur(array<int, 11> state, unordered_map<const array<int, 11>, int, Hash> &cached, vector<int> &a)
{
	int i = state[0];
	if (i == -1) {
		return 0;
	}
	if (cached.find(state) != cached.end()) {
		return cached[state];
	}

	state[0] -= 1;
	int v_a = recur(state, cached, a);

	int n = a[i];
	while (n > 0) {
		int digit = n % 10;
		if (state[digit + 1] == 0) {
			cached[state] = v_a;
			return v_a;
		}
		state[digit + 1]--;
		n /= 10;
	}

	int v_b = recur(state, cached, a) + a[i];

	cached[state] = max(v_a, v_b);
	return max(v_a, v_b);
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	unordered_map<const array<int, 11>, int, Hash> cached;
	array<int, 11> count = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	count[0] = n - 1;
	cout << recur(count, cached, a) << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
