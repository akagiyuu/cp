#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

int f(int i, vector<int> &candies, vector<int> &ratings)
{
	int n = ratings.size();

	if (candies[i] == 0) {
		int val = 0;
		if (i > 0 && ratings[i] > ratings[i - 1]) {
			val = f(i - 1, candies, ratings);
		}
		if (i < n - 1 && ratings[i] > ratings[i + 1]) {
			val = max(val, f(i + 1, candies, ratings));
		}

		candies[i] = val + 1;
	}

	return candies[i];
}

int candy(vector<int> &ratings)
{
	int n = ratings.size();

	vector<int> candies(n, 0);

	for (int i = 0; i < n; i++) {
		bool is_root = true;
		if (i > 0 && ratings[i] > ratings[i - 1])
			is_root = false;
		if (i < n - 1 && ratings[i] > ratings[i + 1])
			is_root = false;

		if (is_root)
			candies[i] = 1;
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
		res += f(i, candies, ratings);
	}

	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> ratings(n);
	for (int i = 0; i < n; i++) {
		cin >> ratings[i];
	}
	cout << candy(ratings) << "\n";
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
