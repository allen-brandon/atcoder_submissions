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
array<vi,200001> adj;
// for subtree i, with k paths available, with a path/no path from parent
ll dp[200001][5][2];
ll a[200001];
ll cur[6];
int par[200001];
int ind[200001];

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(k);
    fill_n(adj.begin(),n+1,vi());
    fr(i,0,n) {
        lli(x);
        a[i] = x;
        fr(j,0,k+1) {
            dp[i][j][0] = 0;
            dp[i][j][1] = 0;
        }
    }
    fr(i,0,n-1) {
        ii(u); ii(v);
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    stack<pair<int,int>> par_st;
    stack<int> st;
    par_st.emplace(0,1);
    while (!par_st.empty()) {
        auto [u,d] = par_st.top();
        par_st.pop();
        ind[u] = adj[u].size();
        if (d==0) {
            if (ind[u]==1 && u!=0) {
                st.push(u);
            }
            continue;
        }
        par_st.emplace(u,0);
        for (int v : adj[u]) {
            if (v==par[u]) continue;
            par[v]=u;
            par_st.emplace(v,1);
        }
    }
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        int p = par[u];
        //try ending here
        fr(j,1,k+1) {
            dp[u][j][1] = a[u];
            dp[u][j][0] = a[u];
        }
        dp[u][0][1] = a[u];

        //try skipping this node
        fill_n(cur,k+1,0);
        for (int v : adj[u]) {
            if (v==p) continue;
            fr(j,1,k+1) {
                fr(j1,1,j) {
                    cur[j] = max(cur[j], cur[j-j1]+dp[v][j1][0]);
                }
            }
        }
        fr(j,1,k+1) dp[u][j][0] = cur[j];
        
        //try assigning one node
        for (int v : adj[u]) {
            if (v==p) continue;
            fill_n(cur,k+1,a[u]);
            for (int v1 : adj[u]) {
                if (v1==p) continue;
                fr(j,1,k+1) {
                    fr(j1,1,j) {
                        cur[j] = max(cur[j], cur[j-j1]+dp[v][j1][v==v1]);
                    }
                }
            }
            //continue a preexisting path from a parent
            fr(j,0,k+1) dp[u][j][1] = max(dp[u][j][1], cur[j]);
            //draw a path from here through only one child
            fr(j,0,k+1) dp[u][j][0] = max(dp[u][j][0], cur[j-1]);
        }
        
        //try assigning two nodes (create a path here)
        for (int c1 : adj[u]) {
            if (c1==p) continue;
            for (int c2 : adj[u]) {
                if (c2==p || c2==c1) continue;
                fill_n(cur,k,a[u]);
                for (int v : adj[u]) {
                    if (v==p) continue;
                    fr(j,1,k) {
                        fr(j1,1,j) {
                            cur[j] = max(cur[j], cur[j-j1]+dp[v][j1][v==c1 || v==c2]);
                        }
                    }
                }
                //draw a path from here using two children
                fr(j,0,k+1) dp[u][j][1] = max(dp[u][j][0], cur[j-1]);
            }
        }
        
        --ind[p];
        if (ind[p]==0) {
            st.push(p);
        }
    }
    // print(dp[0][k][0]);
    fr(i,0,n) {
        print("__" << i << "__");
        vi test;
        fr(j,0,k+1) {
            test.push_back(dp[0][j][0]);
        }
        printv(test);
        print("");
    }
}