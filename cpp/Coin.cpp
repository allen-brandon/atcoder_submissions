#ifdef LOCAL
#include "_pch.hpp"
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define USE_INPUT_FILE(file)
#endif

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned long long;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // find_by_order(), order_of_key()
typedef tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
#define fio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define fr(i,l,r) for (int i=l; i<r; ++i)
#define print(_) cout << _ << "\n";
#define printv(_) for (const auto& x : _) cout << x << ' '; cout << '\n';
#define printm(_) cout<<"{";for (const auto& kvp:_) cout<<kvp.first<<":"<<kvp.second<<","; cout<<"}\n";
#define si(_) string _; cin >> _;
#define ii(_) int _; cin >> _;
#define lli(_) ll _; cin >> _;
array<pair<int,int>,4> didj = {{{-1,0},{0,1},{1,0},{0,-1}}};
array<string,2> ny = {"No","Yes"};
ll inf = 151515151515151;
ll mod = 998244353;
ll a[5001];
ll res[5001];

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    lli(n); lli(m); lli(l);
    fill_n(a,n+1,0);
    a[0] = 1ll;
    ll cur = 0;
    fr(i,1,m+1) {
        //add in ith coin
        int c = i;
        fr(j,c,n+1) {
            ll old_val = a[j];
            a[j] += a[j-c];
            a[j] -= a[j]>=mod? mod : 0ll;
        }
        if (i>=l) {
            int c = i+1-l;
            //print i-lth answer
            res[c-1] = a[n];
            //take out i-lth coin
            for (int j = n; j>=c; j--) {
                ll old_val = a[j];
                a[j] -= a[j-c];
                a[j] += a[j]<0? mod : 0;
            }
        }
    }
    fr(i,0,m+1-l) print(res[i]);
}