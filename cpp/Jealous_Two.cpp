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
#define ordered_set tree<tuple<int,int,int>, null_type, less<tuple<int,int,int>>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_by_key()
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
array<int,200001> a;
array<pair<int,int>,200001> ab;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    for (int i=0; i<n; ++i) cin >> a[i];
    for (int i=0; i<n; ++i) {
        ii(x);
        ab[i] = {a[i],x};
    }
    sort(ab.begin(), ab.begin()+n);
    ll res = 0;
    ordered_set t;
    int l = 0;
    for (int r=0; r<n; ++r) {
        auto [x, y] = ab[r];
        while (ab[l].first != ab[r].first) {
            res+=t.size()-t.order_of_key({ab[l].second,-1,-1});
            ++l;
        }
        t.insert({y,x,r});
    }
    while (l<n) {
        res+=t.size()-t.order_of_key({ab[l].second,-1,-1});
        ++l;
    }
    print(res);
}