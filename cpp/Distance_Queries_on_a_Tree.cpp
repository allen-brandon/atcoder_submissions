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

class SegmentTree {
    private:
    vll a;
    ll total;
    int n;
    int m;
    public:
    SegmentTree(const vll& arr) {
        n = 1;
        m = arr.size();
        while (n<m) n<<=1;
        a = vll(n<<1,0);
        copy(arr.begin(),arr.end(),a.begin()+n);
        fr(i,n,0) a[i] = a[i*2]+a[i*2+1];
    }

    void update(int i, ll x) {
        i+=n;
        total += x-a[i];
        a[i] = x;
        i>>=1;
        while (i!=0) {
            a[i] = a[i*2]+a[i*2]+1;
            i>>=1;
        }
    }

    ll query(int l, int r) {
        if (l==0 && r==m) return total;
        l+=n;
        r+=n;
        ll res = 0;
        while (l<r) {
            if (l&1) {
                res+=a[l];
                ++l;
            }
            if (r&1) {
                --r;
                res+=a[r];
            }
            l>>=1;
            r>>=1;
        }
        return res;
    }

};

array<vector<tuple<int,int,ll>>,200001> adj;
tuple<int,int,ll> edges[200001]; //subtree size for each node
int sz[200001]; //subtree size for each node
int depth[200001]; //depth of each node
int tour[200001][2]; //u -> l,r in euler tour
int anc[200001][18]; //binary lifting array
bitset<200001> hld; //1 = heavy, 0 = light edge
int hld_par[200001][2]; //v1 -> {u1, i}
int hld_map[200001][2]; // u -> (xth hld node, yth idx in x's path)
int roots[200001]; //root node for each path (given hld node's idx)
vll* path_vectors[200001]; // array of edges for each hld node
SegmentTree* paths[200001]; // segment tree for each hld node

int find_lca(int u, int v, int log_lim) {
    if (depth[u]>depth[v]) swap(u,v);
    auto [l,r] = tour[v];
    if (tour[u][0]<l && tour[u][1]>r) return u;
    int p = u;
    for (int j = log_lim-1; j>=0; --j) {
        int p1 = anc[p][j];
        if (tour[p1][0]>l && tour[p1][1]<r) p = p1;
    }
    return anc[p][0];
};

ll dist(int u, int lca) {
    auto [u1,i] = hld_map[u];
    auto [lca1,j] = hld_map[lca];
    ll res;
    while (u1!=lca1) {
        auto [v1, i1] = hld_par[u1];
        res+=(*paths[u1]).query(0,i);
        u1 = v1;
        i = i1;
    }
    if (i!=j) res+=(*paths[u1]).query(i,j);
    return res;
}


int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    int log_lim = log2(n)+1;
    fill_n(adj.begin(), n+1, vector<tuple<int,int,ll>>());
    fr(i,1,n) {
        //Everything is 0-indexed
        ii(u); ii(v); lli(w);
        edges[i] = {u,v,w};
        adj[u-1].emplace_back(v-1,i,w);
        adj[v-1].emplace_back(u-1,i,w);
    }
    int tour_idx_val = 0;
    int* tour_idx = &tour_idx_val;
    auto assign = [](auto& assign, int u, int p, int log_lim, int* tour_idx) -> void {
        //assign size and tour idx
        sz[u] = 1;
        tour[u][0] = *tour_idx;
        ++*tour_idx;
        //assign anc
        anc[u][0] = p;
        int v = p;
        fr(j,1,log_lim) {
            if (v==0) break; //zero-indexed vertices
            anc[u][j] = anc[v][j-1];
            v = anc[v][j-1];
        }
        
        //recurse to children
        for (auto [v,e,w] : adj[u]) {
            if (v==p) continue;
            depth[v] = depth[u]+1;
            assign(assign, v, u, log_lim, tour_idx);
            sz[u]+=sz[v];
        }
        for (auto [v,e,w] : adj[u]) {
            if (v==p) continue;
            if (sz[v]>=sz[u]/2) {
                hld[e] = 1;
                break;
            } else {
                hld[e] = 0;
            }
        }
        tour[u][1] = *tour_idx;
        ++*tour_idx;
    };
    assign(assign, 0, 0, log_lim, tour_idx);
    int m = 0; // number of hld nodes
    int* hld_idx = &m;
    // u: node, p: parent, u1: hld node, i: idx of u in u1's array
    auto build_hld = [](auto& build_hld, int u, int p, int u1, int i, int* hld_idx) -> void {
        for (auto [v,e,w] : adj[u]) {
            if (v==p) continue;
            if (hld[e]==1) {
                (*path_vectors[u1]).push_back(w);
                hld_map[v][0] = hld_map[u][0];
                hld_map[v][1] = hld_map[u][i+1];
                build_hld(build_hld, v, u, u1, i+1, hld_idx);
            } else {
                ++*hld_idx;
                int v1 = *hld_idx;
                path_vectors[v1] = new vll({w});
                hld_map[v][0] = v1;
                hld_map[v][1] = 0;
                hld_par[v1][0] = u1;
                hld_par[v1][1] = i;
                build_hld(build_hld, v, u, v1, 0, hld_idx);
            }
        }
        if (i==0) paths[u1] = new SegmentTree(*path_vectors[u1]);
    };
    path_vectors[0] = new vll();
    build_hld(build_hld, 0, 0, 0, 0, hld_idx);
    ++m;
    //process queries
    ii(queries);
    vll res;
    fr(q,0,queries) {
        ii(t);
        if (t==1) {
            ii(i); lli(w1);
            auto [u,v,w] = edges[i];
            edges[i] = {u,v,w1};
            int u1 = hld_map[u][0], v1 = hld_map[v][0];
            if (u1 == v1) {
                int idx = max(hld_map[u][1], hld_map[v][1]);
                (*paths[u1]).update(idx, w1);
            } else {
                (*paths[u1]).update(0, w1);
            }
        } else {
            ii(u); ii(v);
            --u; --v;
            int lca = find_lca(u,v,log_lim);
            ll cur = dist(u,lca) + dist(v,lca);
            print(u << " " << v);
            print(lca << " (" << dist(u,lca) << ", " << dist(v,lca) << ")");
            res.push_back(cur);
        }
    }
    fr(i,0,res.size()) print(res[i]);
}

//note: hld typically uses largest subtree as heavy path; this only uses subtrees of size >= sz[u]/2