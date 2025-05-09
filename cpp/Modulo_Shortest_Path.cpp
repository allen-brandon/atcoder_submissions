#ifdef DEBUG
#include <cstdio>
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#define USE_INPUT_FILE(file)
#endif

using namespace std;
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
ll inf = 151515151515151;
ll mod = 998244353;
array<string,2> ny = {"No","Yes"};

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    map<int,map<int,int>> adj;
    map<int,int> dist;
    for (int i=1; i<=n; ++i) {
        ii(x);
        adj[-i][(m-x)%m]=0;
        adj[(m-x)%m];
        dist[-i] = m;
        dist[(m-x)%m] = m;
    }
    for (int i=1; i<=n; ++i) {
        ii(x);
        adj[x][-i]=0;
        dist[x] = m;
    }
    int first = -1;
    int prev = -1;
    for (auto [x,_] : adj) {
        if (x<0) continue;
        if (first==-1) {
            first = x;
        }
        else {
            adj[prev][x] = (x-prev+m)%m;
        }
        prev = x;
    }
    adj[prev][first] = (first-prev+m)%m;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.emplace(0,-1);
    dist[-1] = 0;
    while (pq.size() != 0) {
        auto [d, u] = pq.top();
        pq.pop();
        if (u==-n) {
            print(d);
            exit(0);
        }
        if (d>dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (d+w>=dist[v]) continue;
            dist[v] = d+w;
            pq.emplace(d+w,v);
        }
    }
}