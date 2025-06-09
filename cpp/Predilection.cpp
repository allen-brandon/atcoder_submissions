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
array<ll,200001> dp; // 1 indexed
array<ll,200001> pref; // 1 indexed

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    pref[0] = 0;
    for (int i=1; i<=n; ++i) {
        lli(x);
        pref[i] = pref[i-1]+x;
    }
    map<ll,int> seen;
    seen[0] = 0;
    dp[0] = 1;
    for (int i=1; i<=n; ++i) {
        ll x = pref[i];
        dp[i]= (dp[i-1] << 1) % mod;
        int j = (seen.find(x) == seen.end())? 0 : seen[x];
        if (j!=0) dp[i]+=mod-dp[j-1];
        dp[i]%=mod;
        seen[x] = i;
    }
    ll res = 0;
    for (int i=1; i<=n; ++i) {
        if (pref[i]==pref[n]) {
            res+=dp[i]+mod-dp[i-1];
            res%=mod;
        }
    }
    // printv(dp);
    print(res%mod);
}