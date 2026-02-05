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
array<vi,1001> adj;
array<vi,1001> dist;


void testcase() {
    ii(n); ii(m); ii(x); ii(y);
    --x; --y;
    fill_n(adj.begin(),n+1, vi());
    fill_n(dist.begin(),n+1,vi({1001}));
    fr(i,0,m) {
        ii(u); ii(v);
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    priority_queue<pair<vi,int>, vector<pair<vi, int>>, greater<pair<vi, int>>> pq;
    pq.emplace(vi({x}),x);
    dist[x] = vi({x});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d>dist[u]) continue;
        if (u==y) break;
        for (int v : adj[u]) {
            vi d1(d.begin(),d.end());
            d1.push_back(v);
            if (dist[v]<=d1) continue;
            dist[v] = d1;
            pq.emplace(d1,v);
        }
    }
    for (auto z : dist[y]) {
        cout << z+1 << " ";
    }
    cout << "\n";
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(t);
    while (t--) testcase();
}