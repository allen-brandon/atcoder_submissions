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
array<pair<int,int>,300001> edges;
array<int,300001> anc;
array<vi,300001> adj;
array<vi,300001> idcs;

class segment_tree {
    private:
    vll a;
    int n;
    public:
    segment_tree(const vll& arr) {
        n = 1;
        while (n<arr.size()) n<<=1;
        a = vll(n<<1,0);
        copy(arr.begin(), arr.end(), a.begin()+n);
        for (int i=n-1; i>0; --i) {
            a[i] = a[i*2]+a[i*2+1];
        }
    }

    void update(int i, ll x) {
        i+=n;
        a[i]+=x;
        for (i>>=1; i!=0; i>>=1) {
            a[i] = a[i*2]+a[i*2+1];
        }
    }

    ll query(int l, int r) {
        ll res = 0;
        l+=n; r+=n;
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

int main() {
    USE_INPUT_FILE("_input.txt");
    fio;
    ii(n);
    fill_n(adj.begin(), n+1, vi());
    fill_n(idcs.begin(), n+1, vi());
    for (int i=0; i<n-1; ++i) {
        ii(u); ii(v);
        edges[i] = {u,v};
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    stack<tuple<int,int,int>> st;
    st.emplace(1,1,0);
    vll tour;
    while (st.size()!=0) {
        auto [d,u,p] = st.top();
        st.pop();
        if (d==0) {
            idcs[u].push_back(tour.size());
            tour.push_back(1); // 0 if start; 1 if end
            continue;
        }
        st.emplace(0,u,p);
        idcs[u].push_back(tour.size());
        tour.push_back(0);
        anc[u]=p;
        for (int v : adj[u]) {
            if (v==p) continue;
            st.emplace(1,v,u);
        }
    }
    segment_tree tree(tour);
    ii(q);
    ll total = n;
    vll res;
    for (int i=0; i<q; ++i) {
        ii(t);
        if (t==1) {
            ii(x); ii(w);
            int idx = idcs[x][1];
            tree.update(idx,w); //1 indexed
            total+=w;
        } else {
            ii(y);
            auto [u,v] = edges[y-1];
            if (anc[u]==v) swap(u,v);
            int l=idcs[v][0], r=idcs[v][1];
            ll x = tree.query(l,r+1);
            res.push_back(abs((x<<1)-total));
        }
    }
    for (auto x : res) {
        print(x);
    }
}