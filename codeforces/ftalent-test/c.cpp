#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct Meet {
	ll start;
	ll end;
	ll index;
};

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	ll n;
	cin >> n;
	vector<Meet> meets(n);
	for (ll i = 0; i < n; i++) {
		char temp;
		cin >> meets[i].start;
		cin >> temp;
		cin >> meets[i].end;
		cin >> temp;
		cin >> meets[i].index;
	}

	sort(meets.begin(), meets.end(), [](Meet a, Meet b) {
		if (a.end == b.end) {
			return a.index < b.index;
		}

		return a.end < b.end;
	});

	vector<ll> result;
	ll cur_time = -1;
	for (ll i = 0; i < n; i++) {
		if (meets[i].start > cur_time) {
			result.push_back(meets[i].index);
			cur_time = meets[i].end;
		}
	}

	cout << result.size() << "\n";
	for (ll i = 0; i < result.size(); i++) {
		if (i != 0) {
			cout << ", ";
		}
		cout << result[i];
	}
	cout << "\n";
}
