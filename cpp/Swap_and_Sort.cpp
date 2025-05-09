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
#define printum(_) cout<<"{";for (const auto& kvp:_) cout<<kvp.first<<":"<<kvp.second<<","; cout<<"}\n";
#define si(_) string _; cin >> _;
#define ii(_) int _; cin >> _;
#define lli(_) ll _; cin >> _;
ll inf = 151515151515151;
ll mod = 998244353;
array<string,2> ny = {"No","Yes"};
array<int,1001> rt, sz;
array<int,1001> a;
array<int,1001> par;
array<int,1000001> res;
array<map<int,int>,1001> adj;
bitset<1001> seen;

int find(int a) {
    while (rt[rt[a]] != rt[a]) {
        rt[a] = rt[rt[a]];
    }
    return rt[a];
}

bool join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a==b) return false;
    if (sz[b]>sz[a]) {
        rt[a]=b;
        sz[b]+=sz[a];
    } else {
        rt[b]=a;
        sz[a]+=sz[b];
    }
    return true;
}

int solve(int i, int res_idx) {
    if (i==a[i]) {
        return res_idx;
    }
    seen = 0;
    seen[i]=1;
    queue<int> q;
    q.push(i);
    int idx = 0;
    while (idx==0) {
        int u = q.front();
        q.pop();
        for (auto [v,w] : adj[u]) {
            if (seen[v]) continue;
            seen[v] = 1;
            q.push(v);
            par[v]=u;
            if (a[v]==i) {
                idx = v;
                break;
            }
        }
    }
    int v = idx;
    while (v!=i) {
        int u = par[v];
        swap(a[v],a[u]);
        res[res_idx]=adj[u][v];
        ++res_idx;
        v = u;
    }
    return res_idx;
}

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    fill_n(sz.begin(), n+1, 1);
    fill_n(adj.begin(), n+1, map<int,int>());
    for (int i=1; i<=n; ++i) {
        ii(x);
        a[i]=x;
        rt[i]=i;
    }
    ii(m);
    for (int i=1; i<=m; ++i) {
        ii(u); ii(v);
        if (join(u,v)) {
            adj[u][v]=i;
            adj[v][u]=i;
        }
    }
    for (int i=1; i<=n; ++i) {
        if (find(i)!=find(a[i])) {
            print(-1);
            exit(0);
        }
    }
    stack<int> st;
    for (int i=1; i<=n; ++i) {
        if (adj[i].size()==1) {
            st.push(i);
        }
    }
    int res_idx = 0;
    while (st.size()!=0) {
        int u = st.top();
        st.pop();
        res_idx = solve(u,res_idx);
        // print("solving for: " << u << " in topsort");
        for (auto [v,w] : adj[u]) {
            adj[v].erase(u);
            if (adj[v].size()==1) st.push(v);
        }
        adj[u].clear();
    }
    print(res_idx);
    for (int i=0; i<res_idx; ++i) {
        cout << res[i] << " ";
    }
    cout << "\n";
}