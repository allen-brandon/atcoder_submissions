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
ll mod = 998244353;

array<int,100002> root;
array<int,100002> par;
array<set<int>,100002> adj;
array<int,100002> sz;

void reroot(int u) {
    vector<pair<int,int>> st;
    st.emplace_back(u,0);
    while (st.size()!=0) {
        auto [u,p] = st.back();
        st.pop_back();
        for (int v : adj[u]) {
            if (v==p) continue;
            par[v]=u;
            st.emplace_back(v,u);
        }
    }
}

int find(int a) {
    while (root[a]!=root[root[a]]) {
        root[a] = root[root[a]];
    }
    return root[a];
}

int join(int a, int b) {
    int u=a, v=b;
    a = find(a);
    b = find(b);
    if (a==b) return 0;
    if (sz[b]>sz[a]) {
        root[a]=b;
        sz[b]+=sz[a];
        par[u]=v;
        reroot(u);
    } else {
        root[b]=a;
        sz[a]+=sz[b];
        par[v]=u;
        reroot(v);
    }
    adj[u].insert(v);
    adj[v].insert(u);
    return 1;
}


int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n); ii(q);
    fill_n(sz.begin(), n, 1);
    fill_n(par.begin(), n, 0);
    fill_n(adj.begin(), n, set<int>());
    for (int i=1; i<=n; ++i) {
        root[i]=i;
    }
    vll res = {0};
    for (int i=0; i<q; ++i) {
        lli(a); lli(b); lli(c);
        ll xl = res.back();
        ll t = 1+(((a*(1+xl))%mod)%2);
        ll u = 1+(((b*(1+xl))%mod)%n);
        ll v = 1+(((c*(1+xl))%mod)%n);
        if (t==1) {
            // print("connecting " << u << " and " << v);
            join(u, v);
            continue;
        }
        // print("querying " << u << " and " << v);
        int cur;
        if ((par[u]==v) || (par[v]==u)) {
            cur=0;
        } else if (par[par[u]]==v) {
            cur=par[u];
        } else if (par[par[v]]==u) {
            cur=par[v];
        } else if (par[u]==par[v]) {
            cur=par[u];
        } else {
            cur=0;
        }
        res.push_back(cur);
    }
    for (int i=1; i<res.size(); ++i) {
        print(res[i]);
    }
}