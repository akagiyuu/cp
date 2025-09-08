#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

vector<int> maximumBobPoints(int sum, vector<int> &a)
{
	int max_score = 0;
	int max_state = 0;

	for (int state = 0; state < (1 << 12); state += 2) {
		int min_sum = 0;
		int score = 0;
		for (int i = 0; i < 12; i++) {
			if (state & (1 << i)) {
				min_sum += a[i] + 1;
				score += i;
			}
		}
		if (min_sum <= sum && score > max_score) {
			max_score = score;
			max_state = state;
		}
	}

	vector<int> res(12);
	for (int i = 0; i < 12; i++) {
		if (max_state & (1 << i)) {
			res[i] = a[i] + 1;
		}
	}

	for (int i = 0; i < 12; i++) {
        sum -= a[i];
	}
    a[0] += sum;

	return res;
}

void solve()
{
	int sum;
	vector<int> a(12);
	cin >> sum;
	for (int i = 0; i < 12; i++)
		cin >> a[i];
	cpp_dump(maximumBobPoints(sum, a));
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
