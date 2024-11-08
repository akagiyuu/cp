#include <bits/stdc++.h>

#define NAME ""
#define repz(i, a) for (int i = 0; i < a; ++i)
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define repr(i, a, b) for (int i = b; i >= a; --i)
#define ll long long
#define ld long double
#define ii pair<int, int>

using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto& it : a) cin >> it;

    ll res = *max_element(a.begin(), a.end());
    cout << res << '\n';
    int q;
    cin >> q;
    while (q--) {
        int i;
        cin >> i;
        i--;

        int j = i + 1;
        while (j < n && a[j] == 0) j++;

        a[j] += a[i];
        a[i] = 0;
        res = max(res, a[j]);
        cout << res << '\n';
    }
} 

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    // freopen(NAME".inp", "r", stdin);
    // freopen(NAME".out", "w", stdout);

    int t = 1;
    cin >> t;
    while(t--) solve();

    return 0;
}