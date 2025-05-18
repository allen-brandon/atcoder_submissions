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
#define ll long long
#define ull unsigned ll
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
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
array<int,61> a;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); lli(y);
    for (int i=0; i<n; ++i) {
        ii(x);
        a[i] = x;
    }
    map<ll,ll> cache;
    cache[1] = 1;
    cache[0] = 0;
    function<ll(ll)> dfs = [&](ll x){
        if (cache.find(x) != cache.end()) return cache[x];
        int idx = lower_bound(a.begin(), a.begin()+n, y)-a.begin();
        ll lg = a[idx];
        ll sm = a[idx-1];
        ll res = dfs(x%sm)+x/sm;
        if (lg!=x<<1) res = min(res, dfs(abs(x-lg))+1);
        cache[x] = res;
        return cache[x];
    };
    // ll test = dfs(0);
    // print(test);
    ll ret = dfs(y);
    print(ret);
}