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
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_by_key()
#define ordered_multiset tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
#define fio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
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
array<ll,200001> a;
array<ll,200001> b;
ll dp[200001][2][2];

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    for (int i=0; i<n; ++i) {
        lli(x);
        a[i] = x;
    }
    for (int i=0; i<n; ++i) {
        lli(x);
        b[i] = x;
    }
    //x0 is red
    dp[0][0][0] = a[0]; //make x1 red
    dp[0][1][1] = 0; //make x1 blue
    dp[0][0][1] = inf;
    dp[0][1][0] = inf;
    for (int i=1; i<n; ++i) {
        for (int k=0; k<2; ++k) {
            //make xi red
            dp[i][0][k] = min(dp[i-1][1][k], dp[i-1][0][k]+b[i-1])+a[i];
            //make xi blue
            dp[i][1][k] = min(dp[i-1][0][k], dp[i-1][1][k]+b[i-1]);
        }
    }
    //if xn and x1 are the same color then sever them
    dp[n-1][0][0]+=b[n-1];
    dp[n-1][1][1]+=b[n-1];
    ll res = dp[n-1][0][0];
    res = min(res, dp[n-1][0][1]);
    res = min(res, dp[n-1][1][0]);
    res = min(res, dp[n-1][1][1]);
    print(res);
}