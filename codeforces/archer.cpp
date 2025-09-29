#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll a, b, c, d;
	cin >> a >> b >> c >> d;
	double x = a * d;
	double y = b * d - (b - a) * (d - c);
	cout << setprecision(10) << x / y << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
