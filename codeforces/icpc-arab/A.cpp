#include <bits/stdc++.h>
using namespace std;
#define ll unsigned long long

struct State {
    ll val = 0;
    vector<ll> cnt = vector<ll>(10, 0); // Đổi int thành ll
};

ll sum_counts(const vector<ll>& cnt) {
    ll sum = 0;
    for(int i = 0; i < 10; i++) {
        sum += cnt[i];
    }
    return sum;
}

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto& i : a) cin >> i;

    auto ok = [&](const vector<ll>& cnt, ll v) {
        if (v == 0) return cnt[0] < 2;
        vector<ll> tmp(10, 0); 
        for (; v > 0; v /= 10) 
            tmp[v % 10]++;
        
        for (int i = 0; i < 10; ++i)
            if (cnt[i] + tmp[i] > 2) 
                return false;
        return true;
    };

    auto update = [&](vector<ll>& cnt, ll v) {
        if (v == 0) {
            cnt[0]++;
            return;
        }
        for (; v > 0; v /= 10)
            cnt[v % 10]++;
    };

    vector<State> dp(n);

    if (ok(dp[0].cnt, a[0])) {
        dp[0].val = a[0];
        update(dp[0].cnt, a[0]);
    }

    for (int i = 1; i < n; ++i) {
        if (ok(vector<ll>(10, 0), a[i])) { 
            dp[i].val = a[i];
            dp[i].cnt = vector<ll>(10, 0); 
            update(dp[i].cnt, a[i]);
        }
        
        for (int j = 0; j < i; ++j) {
            if (dp[j].val > 0 && ok(dp[j].cnt, a[i])) {
                ll new_val = dp[j].val + a[i];
                if (new_val > dp[i].val) {
                    dp[i].val = new_val;
                    dp[i].cnt = dp[j].cnt;
                    update(dp[i].cnt, a[i]);
                }
            }
        }
    }

    ll res = 0;
    for (int i = 0; i < n; ++i) 
        res = max(res, dp[i].val);
    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 
    cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}
