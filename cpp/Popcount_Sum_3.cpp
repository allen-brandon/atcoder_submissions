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
array<ll,100> res;
bitset<61> bs;
array<array<array<pair<ll,ll>,2>,61>,61> dp; // i,k,eq

ll mod_mul(int i, ll x) { //multiply x by ith power of 2
    ll res = x;
    for (int shift=0; shift<i; ++shift) {
        res<<=1;
        res%=mod;
    }
    return res;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    auto dfs = [](auto &dfs, int i, int k, int eq) {
        if (i<0) return make_pair(ll(k==0), 0ll);
        if (dp[i][k][eq].first != -1) return dp[i][k][eq];
        ll count = 0, total = 0;
        auto [no_count, no_total] = dfs(dfs, i-1, k, eq&(bs[i]==0));
        count+=no_count;
        total+=no_total;
        if (k>0 && (eq==0 || bs[i]==1)) {
            auto [yes_count, yes_total] = dfs(dfs, i-1, k-1, eq);
            // add these into total
            count+=yes_count;
            total+=yes_total;
            total += mod_mul(i, yes_count); //you can add this bit in this many times
        }
        dp[i][k][eq] = make_pair(count%mod, total%mod);
        return dp[i][k][eq];
    };
    for (int test_case=0; test_case<t; ++test_case) {
        lli(n); ii(k);
        for (int i=0; i<61; ++i) {
            for (int j=0; j<61; ++j) {
                fill_n(dp[i][j].begin(), 2, make_pair(-1,-1));
            }
        }
        ll bit = 0;
        while (1ll<<bit<=n) ++bit;
        bit-=1;
        bs = n;
        res[test_case] = dfs(dfs, bit, k, 1).second;
    }
    for (int i=0; i<t; ++i) {
        print(res[i]);
    }
}