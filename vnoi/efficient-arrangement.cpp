#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <bits/stdc++.h>
#define fu(i, a, b) for(int i = (a); i <= (b); i++)
#define fd(i, a, b) for(int i = (a); i >= (b); i--)
#define ll long long
#define bit(mask, x) (mask & (1LL << x))
#define pi pair<int, int>
#define fi first
#define se second
#define mp(x, y) make_pair(x, y)
#define nl cout << '\n';
#define pb push_back
#define pll pair<ll, ll>
#define int ll
using namespace std;
using namespace std::chrono;
//#define double long double
const int N = (int)3e5 + 5;
int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
int dy[8] = {1, -1, 0, 0, -1, 1, -1, 1};
const ll INF = (ll)1e9 + 5;
const ll MOD = (ll)1e9 + 7;
const int LOG = 20;
const ll cow = 37;
const double eps = 0.0001;
const int M =(int)3e5 + 5;

template<class T1>
void print(T1 a)
{
    cout << a << ' ';
}

template<class T1, class T2>
bool maximize(T1 &a, T2 b)
{
    if(a < b)
    {
        a = b;
        return true;
    }
    return false;
}

template<class T1, class T2>
bool minimize(T1 &a, T2 b)
{
    if(a > b)
    {
        a = b;
        return true;
    }
    return false;
}

template<class T1, class T2>
void add(T1 &a, T2 b)
{
    a += b;
    if(a >= MOD) a-=MOD;
}

template<class T1, class T2>
void sub(T1 &a, T2 b)
{
    a -=b;
    if(a < 0) a += MOD;
}
template<class T1, class T2>
void mul(T1 &a, T2 b)
{
    a *= b;
    a%=MOD;
    return a;
}

template<typename T, typename V>
void print(pair<T, V> &p)
{
    print(p.fi);
    print(p.se);
}
template<typename T>
void print(vector<T> v)
{
    for (int i = 0; i < (int)v.size(); i++) print(v[i]);
}
template<typename T>
void print(vector<vector<T>> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
            print(v[i][j]);
        nl;
    }
}
int min3(int a, int b, int c)
{
    return min(a, min(b, c));
}
int n, k;
int a[N];
bool check(int x) {
    int total = x * k;
    int sum = 0;
    fu(i, 1, n) {
        int val = a[i];
        if(val > x) val = x;
        sum+=val;
    }
    if(sum < total) return false;
    return true;
}

void read()
{
    cin >> n >> k;
    fu(i, 1, n) cin >> a[i];
	int sum = 0;
	fu(i, 1, n) sum+=a[i];
    int l = 0, r = sum / k + 500;
    int res = 0;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(check(mid)) {
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    cout << res;
    nl;
}

signed main()
{
//    freopen("AGGRCOW.inp","r",stdin);
//    freopen("AGGRCOW.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int test;
    test = 1;
    cin >> test;
    while(test--)
    {
        read();
        // solve();
    }
}
