#include <bits/stdc++.h>
#include <ios>
#include <string>

using namespace std;

typedef long long ll;

void solve()
{
	ll k;
	cin >> k;
	ll sum = 9;
	ll digit = 1;
	ll pow = 9;
	while (sum < k) {
		digit++;
		pow *= 10;
		sum += pow * digit;
	}
	sum -= pow * digit;
	sum++;
	ll value = (k - sum) / digit + pow / 9;
	ll delete_count = digit - (k - sum) % digit - 1;
	while (delete_count--) {
		value /= 10;
	}
	cout << value % 10 << "\n";
}

int main()
{
	ios_base::sync_with_stdio();
	cin.tie(NULL);
	cout.tie(NULL);
	ll t;
	cin >> t;
	while (t--)
		solve();
}
