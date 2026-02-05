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
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // find_by_order(), order_of_key()
typedef tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
#define vll vector<ll>
#define vi vector<int>
#define counter(_) unordered_map<_,size_t>
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
vi adj[200001];
pair<int,int> dist[200001][2];

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(m);
    fr(i,0,m) {
        ii(u); ii(v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    si(s);
    queue<tuple<int,int,ll>> q;
    fr(i,0,n) {
        if (s[i]=='S') {
            q.emplace(i,i,0);
            dist[i][0] = {i,0};
        } else {
            dist[i][0] = {-1,-1};
        }
        dist[i][1] = {-1,-1};
    }
    while (!q.empty()) {
        auto [u,p,d] = q.front();
        q.pop();
        for (int& v : adj[u]) {
            if (dist[v][0].first == p || dist[v][1].first == p) continue;
            if (dist[v][0].first == -1) {
                dist[v][0] = {p,d+1};
                q.emplace(v,p,d+1);
            } else if (dist[v][1].first == -1) {
                dist[v][1] = {p,d+1};
                q.emplace(v,p,d+1);
            }
        }
    }
    fr(i,0,n) {
        if (s[i]=='D') {
            print(dist[i][0].second + dist[i][1].second);
        }
    }
}