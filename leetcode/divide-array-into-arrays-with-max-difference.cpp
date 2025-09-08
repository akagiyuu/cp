#include <algorithm>
#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

vector<vector<int> > divideArray(vector<int> &nums, int k)
{
	auto n = nums.size();
	auto m = n / 3;
	sort(nums.begin(), nums.end());

	vector<vector<int> > res(m, vector<int>(3));
	for (auto i = 0; i < n; i++) {
		res[i / 3][i % 3] = nums[i];
	}
	for (auto i = 0; i < m; i++) {
		if (res[i][2] - res[i][0] > k)
			return vector<vector<int> >();
	}
	return res;
}

void solve()
{
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<int> nums = {4,2,9,8,2,12,7,12,10,5,8,5,5,7,9,2,5,11};
	auto r = divideArray(nums, 4);
	cpp_dump(r);
	// int t;
	// cin >> t;
	// while (t--)
	// 	solve();
}
