#ifdef DEBUG
#include <cstdio>
#define USE_INPUT_FILE(file) freopen(file, "r", stdin);
#else
#define USE_INPUT_FILE(file)
#endif

using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <deque>
#include <queue>
#include <numeric>
#include <bitset>
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
#define printum(_) cout<<"{";for (const auto& kvp:_) cout<<kvp.first<<":"<<kvp.second<<","; cout<<"}\n";
#define si(_) string _; cin >> _;
#define ii(_) int _; cin >> _;
#define lli(_) ll _; cin >> _;
ll inf = 151515151515151;
ll mod = 1000000007;
array<string,2> ny = {"No","Yes"};
array<vector<pair<ll,ll>>,200002> adj;
array<ll,200002> seen;
array<ll,200002> a;

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    lli(n); lli(m);
    for (ll i=1; i<=n; ++i) {
        cin >> a[i];
    }
    fill_n(adj.begin(), n+1,vector<pair<ll,ll>>());
    fill_n(seen.begin(), n+1,-inf);
    for (ll i=0; i<m; ++i) {
        lli(u); lli(v);
        ll uh = a[u], vh = a[v];
        adj[u].emplace_back(v, vh<uh? uh-vh : (uh-vh)*2);
        adj[v].emplace_back(u, uh<vh? vh-uh : (vh-uh)*2);
    }
    priority_queue<pair<ll,ll>> pq;
    pq.emplace(0,1);
    while (pq.size()!=0) {
        auto [d,u] = pq.top();
        pq.pop();
        if (seen[u]>d) continue;
        for (auto [v, w] : adj[u]) {
            if (seen[v]>=d+w) continue;
            pq.emplace(d+w, v);
            seen[v]=d+w;
        }
    }
    ll res = 0ll;
    for (ll i=1; i<=n; ++i) {
        res = max(res, seen[i]);
    }
    print(res);
}