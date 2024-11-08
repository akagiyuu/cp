#include <bits/stdc++.h>
#include "cpp-dump/cpp-dump.hpp"

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

const int ls[5][5] = { { 0, 1, 1, 2, 2 }, { 1, 0, 2, 3, 3 }, { 1, 2, 0, 1, 1 }, { 2, 3, 1, 0, 2 }, { 2, 3, 1, 2, 0 } };

int solve(vector<int> &choosen)
{
	if (choosen.size() == 5) {
		int pre = choosen[0];
		int l = 0;
		for (int i = 1; i < 5; i++) {
            l += ls[pre][choosen[i]];
            pre = choosen[i];
		}
        return l;
	}

    int l = 0;
	for (int i = 0; i < 5; i++) {
		if (find(choosen.begin(), choosen.end(), i) != choosen.end()) {
			continue;
		}
		choosen.push_back(i);
        l += solve(choosen);
        choosen.pop_back();
	}
    return l;
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    vector<int> choosen(0);
    cout << solve(choosen);

	// int t;
	// cin >> t;
	// while (t--)
	// 	solve();
}
