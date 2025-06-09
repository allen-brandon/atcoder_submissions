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
array<int, 101> a;
array<int, 11> e;
// array<ll,100001> state;
// bitset<100001> used;
array<vector<pair<int,int>>,1001> adj;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m); ii(k);
    for (int i=0; i<m; ++i) {
        ii(x);
        --x;
        a[i] = x;
    }
    fill_n(adj.begin(), n, vector<pair<int,int>>());
    for (int i=0; i<n-1; ++i) {
        ii(u); ii(v);
        --u; --v;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    auto dfs = [](auto& dfs, int u, int p, int t) {
        if (u==t) return 1;
        for (auto [v,i] : adj[u]) {
            if (v==p) continue;
            // print("test" << " " << u << " " << v << " " << i);
            ++e[i];
            if (dfs(dfs,v,u,t)) return 1;
            --e[i];
        }
        return 0;
    };
    for (int i=0; i<m-1; ++i) {
        int u = a[i], v = a[i+1];
        dfs(dfs,u,u,v);
    }
    unordered_map<int,ll> state;
    state[0] = 1;
    for (int i=0; i<n-1; ++i) {
        int x = e[i];
        unordered_map<int,ll> tmp;
        for (auto [y,f] : state) {
            // tmp[y-x]+=f;
            // tmp[y+x]+=f;
            tmp[y-x] = (tmp[y-x]+f)%mod;
            tmp[y+x] = (tmp[y+x]+f)%mod;
        }
        state = tmp;
    }
    print(state[k]);
}