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
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> // find_by_order(), order_of_key()
#define ordered_multiset tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
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
array<int,200001> rt;
array<int,200001> sz;
bitset<200001> cy;

int find(int a) {
    while (rt[a]!=rt[rt[a]]) {
        rt[a] = rt[rt[a]];
    }
    return rt[a];
}

ll join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a==b) {
        if (cy[a]==1) return 0;
        cy[a] = 1;
        return 2;
    }
    if (cy[a]==1 && cy[b]==1) {
        return 0;
    }
    if (sz[b]>sz[a]) {
        rt[a] = b;
        sz[b]+=sz[a];
        cy[b] = cy[b]|cy[a];
    } else {
        rt[b] = a;
        sz[a]+=sz[b];
        cy[a] = cy[a]|cy[b];
    }
    return 1;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    iota(rt.begin(),rt.end(),0);
    fill_n(sz.begin(), n+1, 1);
    fr(i,0,n) cy[i]=0;
    ll res = 1;
    fr(i,0,m) {
        ii(u); ii(v);
        ll x = join(u,v);
        if (x==0) {
            print(0);
            exit(0);
        } else {
            res *= x;
            res%=mod;
        }
    }
    fr(i,1,n+1) {
        if (cy[find(i)]==0) {
            print(0);
            exit(0);
        }
    }
    print(res);
}