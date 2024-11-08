#include <algorithm>
#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<int> z_pos;
	vector<int> o_pos;

	for (int i = 0; i < n; i++) {
		if (s[i] == '1') {
			o_pos.push_back(i);
			continue;
		}
		z_pos.push_back(i);
	}

	auto cal = [z_pos, o_pos, n](int cur_zc) -> int {
		int zi = cur_zc - 1;
        int oi = 0;
		int count = 0;
		while (true) {
			oi = upper_bound(o_pos.begin() + oi, o_pos.end(), z_pos[zi]) - o_pos.begin();
			if (oi == o_pos.size()) {
				break;
			}
			count++;
			zi = upper_bound(z_pos.begin() + zi, z_pos.end(), o_pos[oi]) - z_pos.begin();
			zi += cur_zc - 1;
			if (zi >= z_pos.size()) {
				count--;
				break;
			}
		}
		if (count == 0) {
			return 0;
		}
		return count + (count + 1) * cur_zc;
	};

	int res = o_pos.size();
	for (int cur_zc = 1; cur_zc <= z_pos.size() / 2; cur_zc++) {
		res = max(res, cal(cur_zc));
	}

	cout << res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
