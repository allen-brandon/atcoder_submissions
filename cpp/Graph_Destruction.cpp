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

array<int, 200001> rt;
array<int, 200001> sz;
array<int, 200001> res;
array<vi, 200001> adj;

int find(int a) {
    while (rt[rt[a]] != rt[a]) {
        rt[a] = rt[rt[a]];
    }
    return rt[a];
}

int join(int a, int b) {
    a = find(a); b = find(b);
    if (a==b) return 0;
    if (sz[b]>sz[a]) {
        rt[a] = b;
        sz[b]+=sz[a];
    } else {
        rt[b] = a;
        sz[a]+=sz[b];
    }
    return 1;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    iota(rt.begin(), rt.begin()+n+1, 0);
    fill(sz.begin(), sz.begin()+n+1, 1);
    fill(adj.begin(), adj.begin()+n+1, vi());
    for (int i=0; i<m; ++i) {
        ii(u); ii(v);
        if (u>v) {
            adj[v].push_back(u);
        } else {
            adj[u].push_back(v);
        }
    }
    int cur = 0;
    for (int u=n; u>0; --u) {
        if (u == find(u)) ++cur;
        for (auto v : adj[u]) {
            cur-=join(u,v);
        }
        res[u] = cur;
        // print(u << " " << cur);
    }
    for (int i=2; i<=n+1; ++i) print(res[i]);
}