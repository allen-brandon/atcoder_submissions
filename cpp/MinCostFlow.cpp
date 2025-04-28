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
array<array<int, 102>,102> adj;
array<array<int, 102>,102> cost;
array<array<int, 102>,102> flow;
array<array<char,50>,50> res;
array<int, 102> pred; // rows: 0-n-1, cols: n-n+m-1, s: n+m, t: n+m+1

int min_cost_max_flow(int n, int k, int s, int t) {
    auto enc = [n](int i, int j) { return i*n+j; };
    auto dec = [n](int idx) { return make_pair(idx/n, idx%n); };
    int found = 0;
    while (1) {
        fill_n(pred.begin(), t+1, -1);
        priority_queue<pair<int,int>> pq;
        pq.emplace(0,s);
        while (!found && pq.size()!=0) {
            auto [w, u] = pq.top();
            if (u==t) {
                found=1;
                
                break;
            }
            if (u<n+n && adj[u][t]-flow[u][t]) {
                
            }

        }
        if (!found) break;
    }
    ll val = 0ll;
    return val;
}
int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(k);
    int s=n+n, t=n+n+1;
    for (int i=0; i<n; ++i) {
        adj[s][i]=k;
        cost[s][i]=0;
        flow[s][i]=0;
        flow[i][s]=0;
        int j=i+n;
        adj[j][t]=k;
        cost[j][t]=0;
        flow[j][t]=0;
        flow[t][j]=0;
        for (int j=n; j<s; ++j) {
            ii(x);
            adj[i][j]=1;
            flow[i][j]=0;
            flow[j][i]=0;
            cost[i][j]=x;
        }
    }
    for (int i=0; i<n+n; ++i) {
        auto row = cost[i];
        vector<int> cur(row.begin(), row.begin()+n+n);
        printv(cur);
    }
    // ll val = min_cost_max_flow(n,k,s,t);
    // print(val);
    for (int i=0; i<n; ++i) {
        string s(res[i].begin(), res[i].begin()+n);
        print(s);
    }
}