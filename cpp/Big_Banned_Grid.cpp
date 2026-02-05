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
array<pair<int,int>,8> didj = {{{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}}};
array<string,2> ny = {"No","Yes"};
ll inf = 151515151515151;
ll mod = 998244353;
array<pair<int,int>,200001> a;
int rt[200002];
int sz[200002];
int find(int a) {
    while (rt[rt[a]] != rt[a]) {
        rt[a] = rt[rt[a]];
    }
    return rt[a];
}
void join(int a, int b) {
    a = find(a); b = find(b);
    if (a==b) return;
    if (sz[b]>sz[a]) {
        rt[a] = b;
        sz[b]+=sz[a];
    } else {
        rt[b] = a;
        sz[a]+=sz[b];
    }
    return;
}
int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(h); ii(w); ii(k);
    map<pair<int,int>,int> d;
    fr(i,0,k) {
        rt[i] = i;
        sz[i] = 1;
    }
    rt[k] = k; sz[k] = 1;
    rt[k+1] = k+1; sz[k+1] = 1;
    fr(i,0,k) {
        ii(y); ii(x);
        a[i] = {x,y};
        d[make_pair(x,y)] = i;
        for (auto [di,dj] : didj) {
            int i1=x+di, j1=y+dj;
            pair<int,int> p = make_pair(i1,j1);
            if (d.find(p)!=d.end()) {
                join(d[p], i);
            }
        }
        if (x==1 || y==h) {
            join(i,k);
        }
        if (y==1 || x==w) {
            join(i,k+1);
        }
    }
    bool res = find(k)!=find(k+1);
    print(ny[res])
}